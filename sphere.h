#pragma once

#include "Hittable.h"

class sphere : public Hittable {
  public:
    /**
     * Default Constructor
     * Sets center to the zero vector and radius to 0
     */
    sphere() {}

    virtual ~sphere() {} // testing

    /**
     * Constructor setting the center to the given center and 
     * radius to the given radius
     * 
     * @param center point3 representing the center of the sphere to create
     * @param radius double representing the radius of the sphere to create
     * @param material_ptr a shared pointer to the class of the material of the sphere 
     */
    sphere(point3 center, double radius, std::shared_ptr<Material> material_ptr);

    // see hittable docs
    virtual bool wasHit(const ray& kRay, double min_t, double max_t, 
        HitRecord& hit_record) const override;

  private:
    // point3 representing the center of the sphere
    point3 center_;
    // double representing the radius of the sphere
    double radius_;
    // shared pointer to the class of the material of the sphere
    std::shared_ptr<Material> material_ptr_;
};
