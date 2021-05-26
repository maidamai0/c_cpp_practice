import ctypes
import os


def main():
    lib_name = os.path.join(os.path.abspath(
        '../../build/bin'), "cppmodule.dll")
    c_lib = ctypes.CDLL(lib_name)
    print(f"lib is {c_lib}")

    # return string
    c_lib.hello.restype = ctypes.c_char_p
    print(f"c_lib says {c_lib.hello().decode()}")

    # add two integers
    print(f"c_lib says 1+2 = {c_lib.sum(1,2)}")

    # add two integers with double
    c_lib.add_double.restype = ctypes.c_double
    print(f"c_lib says 1+2.3 = {c_lib.add_double(1,ctypes.c_double(2.3)):.1f}")


if __name__ == "__main__":
    main()
