#pragma once

/**
 * Abstract Class representing a Material
 */
class Material {
  public:
    virtual ~Material() {}
    /**
     * Scatters or absorbs the given ray and returns how much the ray has been 
     * attenuated (reduced in force) as well as the scattered ray
     * 
     * @param kRay a constant reference to a ray to be scattered 
     * @param kHitRecord a constant reference to a HitRecord storing the point of intersection, surface normal, 
     *     and t value of a ray hitting a hittable object
     * @param attenuation a reference to a color to be updated with how much the given ray is attenuated
     * @param scattered_ray a reference to a ray to be updated with the scattered ray
     * @return a bool that is true if the ray was scattered and false if the ray was absorbed
     */
    virtual bool scatter(const ray& kRay, const HitRecord& kHitRecord, 
        color& attenuation, ray& scattered_ray) const = 0;
};

/**
 * Class representing a Lambertian (diffuse) Material
 */
class Lambertian : public Material {
  public:
    /**
     * Constructor that sets the lambertian material's albedo to the given albedo
     * 
     * @param albedo_ constant reference to a color representing the laberian material's albedo
     */ 
    Lambertian(const color& kAlbedo) : albedo_(kAlbedo) {}

    // see Material class docs
    virtual bool scatter(const ray& kRay, const HitRecord& kHitRecord, 
        color& attenuation, ray& scattered_ray) const override {
      vec3 scatter_direction = kHitRecord.surface_normal_ + randomUnitVector();
      // guard against scatter direction that is close to 0
      if (scatter_direction.nearZero()) {
        scatter_direction = kHitRecord.surface_normal_;
      }
      scattered_ray = ray(kHitRecord.point_of_intersection_, scatter_direction);
      attenuation = albedo_;
      return true;
    }

  private:
    // color that stores the Lambertian Material's albedo (ability to reflect sunlight)
    color albedo_;
};

/**
 * Class representing a Metal Material
 */
class Metal : public Material {
  public:
    /**
     * Constructor that sets the metal material's albedo to the given albedo
     * 
     * @param albedo constant reference to a color representing the metal material's albedo
     * @param fuzziness double representing how fuzzy the metal's reflection is
     */ 
    Metal(const color& kAlbedo, double fuzziness) : albedo_(kAlbedo) {
      if (fuzziness >= 1) {
        fuzziness_ = 1;
      } else {
        fuzziness_ = fuzziness;
      }
    }

    // see Material class docs
    virtual bool scatter(const ray& kRay, const HitRecord& kHitRecord, 
        color& attenuation, ray& scattered_ray) const override {
      const vec3 kReflectedRay = reflect(unitVector(kRay.direction()), kHitRecord.surface_normal_);
      scattered_ray = ray(kHitRecord.point_of_intersection_, kReflectedRay 
          + randomPointInUnitSphere() * fuzziness_);
      attenuation = albedo_;
      return (dot(scattered_ray.direction(), kHitRecord.surface_normal_) > 0);
    }

  private:
    // color that stores the Metal Material's albedo (ability to reflect sunlight)
    color albedo_;
    // double storing how fuzzy the reflection is (1 is completely fuzzy, 0 is no fuzziness)
    double fuzziness_;
};

/**
 * Class that reprents a Dielectric Material that always refracts
 */
class Dielectric : public Material {
  public:
    /**
     * Constructor that sets the dielectric material's index of refraction to the given 
     * index of refraction
     * 
     * @param index_of_refraction double representing the index of refraction of the 
     *    dielectric material
     */ 
    Dielectric(double index_of_refraction) : index_of_refraction_(index_of_refraction) {}

    // see Material class docs
    virtual bool scatter(const ray& kRay, const HitRecord& kHitRecord, 
        color& attenuation, ray& scattered_ray) const override {
      attenuation = color(1.0, 1.0, 1.0);

      double refraction_ratio;
      if (kHitRecord.front_facing_) {
        refraction_ratio = 1.0 / index_of_refraction_;
      } else {
        refraction_ratio = index_of_refraction_;
      }

      const vec3 kRefractedRay = refract(unitVector(kRay.direction()), kHitRecord.surface_normal_, 
          refraction_ratio);
      scattered_ray = ray(kHitRecord.point_of_intersection_, kRefractedRay);
      return true;
    }

  private:
    /** 
     * Double storing the index of refraction of the dielectric material
     * 
     * Common index of refraction values: 
     *  1.0 ~ air
     *  1.3 - 1.7 ~ glass
     *  2.4 ~ diamond
     */
    double index_of_refraction_;
};
