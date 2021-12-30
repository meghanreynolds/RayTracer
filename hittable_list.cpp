#include "hittable_list.h"

hittable_list::hittable_list(std::shared_ptr<Hittable> object) {
  add(object);
}

void hittable_list::clear() {
  objects_.clear();
}

void hittable_list::add(std::shared_ptr<Hittable> object) {
  objects_.push_back(object);
}

bool hittable_list::wasHit(const ray& kRay, double min_t, double max_t, 
    HitRecord& hit_record) const {
  HitRecord temp_hit_record = HitRecord();
  bool has_hit_anything = false;
  double closest_t_value = max_t;

  for (std::shared_ptr<Hittable> object : objects_) {
    if (object->wasHit(kRay, min_t, closest_t_value, temp_hit_record)) {
      closest_t_value = temp_hit_record.t_;
      has_hit_anything = true;
      // only update hit record when new closest intersection occurs
      hit_record = temp_hit_record;
    }
  }
  return has_hit_anything;
}
