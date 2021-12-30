#pragma once

#include <memory>
#include <vector>

#include "Hittable.h"

/**
 * Class that stores a list of hittable objects
 */
class hittable_list : public Hittable {
  public:
    /**
     * Default Constructor (makes empty list)
     */
    hittable_list() {}

    /**
     * Constructor adding the given object to the list
     * 
     * @param hittable_object a pointer to a hittable object to 
     *     add to the new list
     */
    hittable_list(std::shared_ptr<Hittable> object);

    /**
     * Clears the contents of the list
     */
    void clear();

    /**
     * Adds the given pointer to a hittable object to the list
     * 
     * @param object a shared pointer to a hittable object to add to the list
     */
    void add(std::shared_ptr<Hittable> object);

    /**
     * Returns true if any of the objects in the list are hit by the given ray
     * Updates hit record with the closest intersection data (does nothing if no hits)
     * 
     * @param kRay constant reference to the ray to check if it hits a 
     *     hittable object in the list
     * @param min_t double representing the minimum t value for the intersection
     * @param max_t double representing the maximum t value for the intersection
     * @param hit_record reference to a hit record to update with the details of the
     *     intersection of the ray and the closest hit object (not updated if no 
     *     objects in the list are hit within the acceptable t value range)
     * @return true if a hittable object in the list was hit by the given ray in the 
     *     given range of values for t and false otherwise
     */
    virtual bool wasHit(const ray& kRay, double min_t, double max_t, 
        HitRecord& hit_record) const override;

  private:
    // vector of shared pointers to hittable objects storing the hittable objects in the list
    std::vector<std::shared_ptr<Hittable>> objects_;
};
