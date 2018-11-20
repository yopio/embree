#include <iostream>
/*
// ---------------------------------------------------------------------------
*/
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>
/*
// ---------------------------------------------------------------------------
*/
#include <OpenImageIO/imageio.h>
/*
// ---------------------------------------------------------------------------
*/
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
/*
// ---------------------------------------------------------------------------
*/
#include "pinhole_camera.h"
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
auto Render(const RTCScene& scene) -> void
{
  RTCIntersectContext context;
  rtcInitIntersectContext(&context);

  // Image setup.
  static constexpr auto kWidth   = 720;
  static constexpr auto kHeight  = 480;
  static constexpr auto filename = "geometry_intersection_test.png";
  static constexpr auto channels = 4;

  // Allocate image buffer.
  float* pixels = new float[kWidth * kHeight * channels];

  // Camera setup.
  auto wtoc   = glm::lookAt(glm::vec3(0, 0, -5),
                            glm::vec3(0, 0,  0),
                            glm::vec3(0, 1,  0));
  auto camera = PinholeCamera(wtoc, 0.035);

  // Render the scene.
  for(int y = 0; y < kHeight; ++y)
  {
    for(int x = 0; x < kWidth; ++x)
    {
      const auto idx = (y * kWidth + x) * 4;

      const auto px = static_cast<float>(x) / static_cast<float>(kWidth);
      const auto py = static_cast<float>(y) / static_cast<float>(kHeight);

      // Ray generation.
      RTCRay ray;
      camera.GenerateRay(px, py, &ray);

      // Ready for intersection test.
      RTCRayHit rayhit;
      rayhit.ray = ray;
      rayhit.hit.geomID    = RTC_INVALID_GEOMETRY_ID;
      rayhit.hit.instID[0] = RTC_INVALID_GEOMETRY_ID;

      // Intersection test.
      rtcIntersect1(scene, &context, &rayhit);

      if(rayhit.hit.geomID != RTC_INVALID_GEOMETRY_ID)
      {
        // Hit
        pixels[idx + 0] = 1.0f;
        pixels[idx + 1] = 1.0f;
        pixels[idx + 2] = 1.0f;
        pixels[idx + 3] = 1.0f;
        continue;
      }
      pixels[idx + 0] = 0.0f;
      pixels[idx + 1] = 0.0f;
      pixels[idx + 2] = 0.0f;
      pixels[idx + 3] = 1.0f;
    }
  }

  // Save image.
  auto *out = OIIO::ImageOutput::create(filename);
  if(!out)
  {
    std::cerr << "Failed to create a output image." << std::endl;
    return ;
  }
  auto spec = OIIO::ImageSpec(kWidth, kHeight, channels, OIIO::TypeDesc::FLOAT);
  out->open(filename, spec);
  out->write_image(OIIO::TypeDesc::FLOAT, pixels);
  out->close();
  OIIO::ImageOutput::destroy(out);

  delete [] pixels;
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

  Render(scene);

  rtcReleaseScene(scene);
  rtcReleaseDevice(device);
}
