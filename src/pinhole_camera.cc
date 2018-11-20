#include "pinhole_camera.h"
/*
// ---------------------------------------------------------------------------
*/
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
/*
// ---------------------------------------------------------------------------
*/
PinholeCamera::PinholeCamera
(
 const glm::mat4& world_to_camera,
 float distance
) :
  world_to_camera_(world_to_camera),
  camera_to_world_(glm::inverse(world_to_camera)),
  sensor_size_(glm::vec2(0.032, 0.024)),
  distance_(distance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto
PinholeCamera::GenerateRay(float x, float y, RTCRay* ray)
const noexcept -> float
{
  static auto scale = glm::scale(glm::mat4(1), glm::vec3(1, 1, -1));

  // Compute a position on sensor.
  auto org = glm::vec3(-(x * sensor_size_.x - sensor_size_.x * 0.5),
                         y * sensor_size_.y - sensor_size_.y * 0.5,
                       distance_);

  // Compute ray direction.
  auto dir = glm::vec3(0) - org;

  // org = Vector3f(0, 0, 0);
  // dir = Vector3f(0, 0, -1);

  // Transform ray origin and direction in camera space into world space.
  org = camera_to_world_ * glm::vec4(org, 1);
  dir = camera_to_world_ * glm::vec4(dir, 0);

  // Initialize ray structure.
  ray->org_x = org.x;
  ray->org_y = org.y;
  ray->org_z = org.z;

  ray->dir_x = dir.x;
  ray->dir_y = dir.y;
  ray->dir_z = dir.z;

  ray->tnear = 0.01f;
  ray->tfar  = 10000.0f;
  ray->time  = 0;

  return 0.0f;
}
/*
// ---------------------------------------------------------------------------
*/
