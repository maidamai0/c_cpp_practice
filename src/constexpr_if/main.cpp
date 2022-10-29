#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

class OGLWidget final {
  template <typename WidgetType>
  friend class MeshCanvas;

 public:
  OGLWidget() { std::cout << __FUNCTION__ << std::endl; }

  ~OGLWidget() { std::cout << __FUNCTION__ << std::endl; }

 private:
  auto call_ogl_only() { std::cout << __FUNCTION__ << std::endl; }

  auto call_common() {
    std::cout << __FUNCTION__ << std::endl;
    return true;
  }

  auto call_common_ogl() {
    std::cout << __FUNCTION__ << std::endl;
    return std::string{__FUNCTION__};
  }
};

class VTKWidget final {
  template <typename WidgetType>
  friend class MeshCanvas;

 public:
  VTKWidget() { std::cout << __FUNCTION__ << std::endl; }

  ~VTKWidget() { std::cout << __FUNCTION__ << std::endl; }

 private:
  auto call_vtk_only() { std::cout << __FUNCTION__ << std::endl; }

  auto call_common() {
    std::cout << __FUNCTION__ << std::endl;
    return true;
  }

  auto call_common_vtk() {
    std::cout << __FUNCTION__ << std::endl;
    return std::string{__FUNCTION__};
  }
};

template <typename WidgetType>
class MeshCanvas {
  using widget_type = WidgetType;
  static constexpr auto is_ogl = std::is_same_v<widget_type, OGLWidget>;
  static constexpr auto is_vtk = std::is_same_v<widget_type, VTKWidget>;

 public:
  // static_assert makes better compiler error message
  auto CallOGLOnly() {
    static_assert(is_ogl, "Only OGLWidget supported");
    return widget_->call_ogl_only();
  }

  // static_assert makes better compiler error message
  auto CallVtkOnly() {
    static_assert(is_vtk, "Only VTKWidget supported");
    return widget_->call_vtk_only();
  }

  // ordinary usage
  auto CallCommon() { return widget_->call_common(); }

  // use [constexpr if statement](https://en.cppreference.com/w/cpp/language/if#Constexpr_If)
  // to select different method at compile time. c++17 supported compiler needed.
  auto CallCommonDifferent() {
    if constexpr (is_ogl) {
      return widget_->call_common_ogl();
    } else {
      return widget_->call_common_vtk();
    }
  }

 private:
  std::unique_ptr<widget_type> widget_ = std::make_unique<widget_type>();
};

auto main(int argc, char** argv) -> int {
  {
    // OGL mesh widget test
    MeshCanvas<OGLWidget> ogl_mesh_canvas;
    ogl_mesh_canvas.CallOGLOnly();
    ogl_mesh_canvas.CallCommon();
    ogl_mesh_canvas.CallCommonDifferent();

    // will trigger a compile error
    // ogl_mesh_canvas.CallVtkOnly();
  }

  std::cout << std::endl;

  {
    // VTK mesh widget test
    MeshCanvas<VTKWidget> vtk_mesh_canvas;
    vtk_mesh_canvas.CallVtkOnly();
    vtk_mesh_canvas.CallCommon();
    vtk_mesh_canvas.CallCommonDifferent();

    // will trigger a compile error
    // vtk_mesh_canvas.CallOGLOnly();
  }
}