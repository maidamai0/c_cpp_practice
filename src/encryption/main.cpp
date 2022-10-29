#include <openssl/aes.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

namespace {
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; (i < 4); i++) ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 3; j++) char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++) ret += base64_chars[char_array_4[j]];

    while ((i++ < 3)) ret += '=';
  }

  return ret;
}

std::string base64_decode(std::string const &encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_];
    in_++;
    if (i == 4) {
      for (i = 0; i < 4; i++) char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++) ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 4; j++) char_array_4[j] = 0;

    for (j = 0; j < 4; j++) char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
}  // namespace

// reference
// https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

const unsigned char *key = (unsigned char *)"2d1ed163630548fdbe1d2ad03f8f63f6";
const unsigned char *iv = (unsigned char *)"aa787bcd23c44c2d";
using unsigned_string = std::basic_string<unsigned char>;

int error_cb(const char *str, size_t len, void *u) {
  (void)u;
  std::cerr << std::string(str, len) << std::endl;
  return 0;
}

// return base64 encoded string
std::string encrypt(const std::string plaintext) {
  int ciphertext_len;
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (ctx == nullptr) {
    return {};
  }

  /*
   * Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
    std::string{};
  }

  unsigned_string plain_string;
  std::copy(plaintext.cbegin(), plaintext.cend(), std::back_inserter(plain_string));

  unsigned_string encrypted_string;
  encrypted_string.resize(plain_string.size() + EVP_CIPHER_CTX_block_size(ctx));

  /*
   * Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */

  int len = 0;
  if (1 != EVP_EncryptUpdate(ctx, encrypted_string.data(), &len, plain_string.data(), plain_string.size())) {
    return std::string{};
  }
  ciphertext_len = len;

  /*
   * Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if (1 != EVP_EncryptFinal_ex(ctx, encrypted_string.data() + len, &len)) {
    return std::string{};
  }
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return base64_encode(encrypted_string.data(), ciphertext_len);
}

std::string decrypt(std::string const &base64_encoded_string) {
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (ctx == nullptr) {
    return {};
  }

  /*
   * Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
    return {};
  }

  auto debase64_string = base64_decode(base64_encoded_string);

  unsigned_string encrypted_string;
  std::copy(debase64_string.cbegin(), debase64_string.cend(), std::back_inserter(encrypted_string));

  unsigned_string plain_string;
  plain_string.resize(encrypted_string.size());

  int len = 0;

  /*
   * Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary.
   */
  if (1 != EVP_DecryptUpdate(ctx, plain_string.data(), &len, encrypted_string.data(), encrypted_string.size())) {
    return {};
  }
  int plaintext_len = len;

  /*
   * Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if (1 != EVP_DecryptFinal_ex(ctx, plain_string.data() + len, &len)) {
    return {};
  }
  plaintext_len += len;
  plain_string.resize(plaintext_len);

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  std::string ret;
  std::copy(plain_string.cbegin(), plain_string.cend(), std::back_inserter(ret));

  return ret;
}

int main(int argc, char **argv) {
  ERR_print_errors_cb(error_cb, nullptr);
  std::string password = "123456ac6gd3@S";
  if (argc > 1) {
    password = argv[1];
  }

  auto encrypted = encrypt(password);
  std::cout << "encrypted: " << encrypted << std::endl;

  auto decrypted_password = decrypt(encrypted);
  assert(decrypted_password == password);
  std::cout << "decrypted: " << decrypted_password << std::endl;

  return 0;
}