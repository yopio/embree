#ifndef _PINHOLE_CAMERA_H_
#define _PINHOLE_CAMERA_H_
/*
// ---------------------------------------------------------------------------
*/
#include <glm/glm.hpp>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>
//! ----------------------------------------------------------------------------
//! @class PinholeCamera
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class PinholeCamera
{
protected:
  glm::mat4 camera_to_world_;
  glm::mat4 world_to_camera_;

  glm::vec2 sensor_size_; // [m]
  float     distance_;    // Sensor to pinhole. [m]

public:
  //! The default class constructor.
  PinholeCamera() = default;

  //! The class constructor with argments.
  PinholeCamera
  (
   const glm::mat4& world_to_camera,
   float distance
  );

  //! The copy constructor of the class.
  PinholeCamera(const PinholeCamera& cam) = default;

  //! The move constructor of the class.
  PinholeCamera(PinholeCamera&& cam) = default;

  //! The default class destructor.
  virtual ~PinholeCamera() = default;

  //! The copy assignment operator of the class.
  auto operator=(const PinholeCamera& cam) -> PinholeCamera& = default;

  //! The move assignment operator of the class.
  auto operator=(PinholeCamera&& cam) -> PinholeCamera& = default;

public:
  /*!
   * @fn float GenerateRay ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto
  GenerateRay(float x, float y, RTCRay* ray)
  const noexcept -> float;

}; // class PinholeCamera
/*
// ---------------------------------------------------------------------------
*/
#endif // _PINHOLE_CAMERA_H_
