#include <iostream>
/*
// ---------------------------------------------------------------------------
*/
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>
/*
// ---------------------------------------------------------------------------
*/
#include <glm/glm.hpp>
/*
// ---------------------------------------------------------------------------
*/
struct Vertex
{
  glm::fvec3 position;
};
/*
// ---------------------------------------------------------------------------
*/
struct Triangle
{
  glm::uvec3 position_indices;
};
/*
// ---------------------------------------------------------------------------
*/
auto Render() -> void
{
  static constexpr auto kWidth  = 512;
  static constexpr auto kHeight = 512;

  
}
/*
// ---------------------------------------------------------------------------
*/
auto main() -> int
{
  // Initialize RTCDevice.
  auto device = rtcNewDevice(""); // configuration

  // Initialize RTCScene.
  auto scene  = rtcNewScene(device);
  rtcSetSceneBuildQuality(scene, RTC_BUILD_QUALITY_HIGH);
  rtcSetSceneFlags(scene, RTC_SCENE_FLAG_NONE);

  // Create a triangle.
  auto geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
  auto vert
    = reinterpret_cast<Vertex*>(rtcSetNewGeometryBuffer(geom,
                                                        RTC_BUFFER_TYPE_VERTEX,
                                                        0,
                                                        RTC_FORMAT_FLOAT3,
                                                        sizeof(glm::vec3),
                                                        3));
  vert[0].position = glm::vec3(-0.5, -0.433, 0);
  vert[1].position = glm::vec3( 0.5, -0.433, 0);
  vert[2].position = glm::vec3( 0.0,  0.433, 0);

  auto tri
    = reinterpret_cast<Triangle*>(rtcSetNewGeometryBuffer(geom,
                                                          RTC_BUFFER_TYPE_INDEX,
                                                          0,
                                                          RTC_FORMAT_UINT3,
                                                          sizeof(Triangle),
                                                          1));
  tri[0].position_indices = glm::uvec3(0, 1, 2);

  // Update geometry.
  rtcCommitGeometry(geom);
  auto geometry_id = rtcAttachGeometry(scene, geom);
  rtcReleaseGeometry(geom);

  // Update scene.
  rtcCommitScene(scene);

  rtcReleaseScene(scene);
  rtcReleaseDevice(device);
}
