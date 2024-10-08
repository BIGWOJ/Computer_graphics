//
//  CRayTrace.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"


/// \fn compPrimaryRayMatrix(CCamera cam, glm::mat3& m)
/// \brief Computation of the projection matrix.
/// \param cam Camera parameters.
/// \param m Output projection matrix.
///
bool CRayTrace::compPrimaryRayMatrix(const CCamera& cam, glm::mat3& m) {

//OBLICZANIE PARAMETRÓW MACIERZY RZUTOWANIA

    glm::vec3 look = cam.lookp - cam.eyep;
    glm::vec3 u = glm::normalize(glm::cross(cam.up, look));
    glm::vec3 v = glm::normalize(glm::cross(u, look));
    glm::vec3 o = ((look / glm::length(look)) * (cam.width / (2.0f*glm::tan((cam.fov * 3.14f / 180.0f)/2.0f)))) - (((cam.width / 2.0f) * u) + ((cam.height / 2.0f * v)));

//PRZYPISYWANIE PARAMETRÓW WEKTORÓW u, v, o DO MACIERZY

    m[0][0] = u[0];
    m[0][1] = u[1];
    m[0][2] = u[2];

    m[1][0] = v[0];
    m[1][1] = v[1];
    m[1][2] = v[2];

    m[2][0] = o[0];
    m[2][1] = o[1];
    m[2][2] = o[2];

    return true;
}


/// \fn rayTrace(CScene scene, CRay& ray, COutput& out)
/// \brief Traces single ray.
/// \param scene Object with all scene components including a camera.
/// \param ray Ray parameter (primary and secondary rays).
/// \param out Object with output color and parameters used in recursion.
///
bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& out) {

    //Obliczenie najbliższego przeciącia z obiektem
    //Ustawienie koloru przeciętego obiektu, w przeciwnym razie ustawienie koloru tła
    CObject* obj;
    CObject* hit_obj;
    float tmin = FLT_MAX;
    float EPS = 0.0001;
    bool is_intersection = false;

    for (int i = 0; i < scene.objectList.size(); i++)
    {
        obj = scene.objectList[i];
        float t = obj->intersect(ray);
        if (t > EPS && t < tmin) {
            tmin = t;
            is_intersection = true;
            hit_obj = scene.objectList[i];
        }
    }

    if (!is_intersection)
    {
        return false;
    }

    float cos_angle, cos_beta;
    glm::vec3 n, L, h, V;

    glm::vec3 p = ray.pos + tmin * ray.dir;
    //V = glm::normalize(-ray.dir);
    n = hit_obj->normal(p);

    for (int i = 0; i < scene.lightList.size(); i++)
    {
        //out.col = out.col + scene.lightList[i].color * hit_obj->matAmbient;
        L = glm::normalize(scene.lightList[i].pos - p);
        CRay shadow;
        shadow.pos = p;
        shadow.dir = L;

        out.col = out.col + out.energy * scene.lightList[i].color * hit_obj->matAmbient;

        bool shadow_intersection = false;
        for (int j = 0; j < scene.objectList.size(); j++)
        {
            if(scene.objectList[j] == hit_obj) {
                continue;
            }

            float t = scene.objectList[j]->intersect(shadow);
            if(t > EPS && t < tmin)
            {
                shadow_intersection = true;
                break;
            }
        }

        if(shadow_intersection) {
            //out.col = out.col + hit_obj->matAmbient;
            continue;
        }

        cos_angle = glm::dot(n, L);
        if (cos_angle > 0.001)
        {
            out.col = out.col + out.energy * scene.lightList[i].color * hit_obj->matDiffuse * cos_angle;
            V = -ray.dir;
            h = glm::normalize(L + V);
            cos_beta = glm::dot(n, h);
            if (cos_beta > 0.001)
            {
                out.col = out.col + out.energy * scene.lightList[i].color * hit_obj->matSpecular * glm::pow(cos_beta, hit_obj->matShininess);
            }
        }

        int MAX_RAY_TREE = 1;
        float MIN_RAY_ENERGY = 0.01;
        if(hit_obj->reflectance > 0 && out.tree < MAX_RAY_TREE && out.energy > MIN_RAY_ENERGY)
        {
            out.tree++;
            out.energy = out.energy * hit_obj->reflectance;
            CRay secondary_ray = reflectedRay(ray, n, p);
            rayTrace(scene, secondary_ray, out);
        }

    }




    /// looks for the closest object along the ray path
    /// returns false if there are no intersection

    /// computes 3D position of the intersection point

    /// computes normal vector at intersection point

    /// for each light source defined in the scene

    /// computes if the intersection point is in the shadows

    /// computes diffuse color component

    /// computes specular color component

    /// adds texture for textured spheres

//    if (hit_obj->isTexture)
//    {
//        glm::vec2 uv = hit_obj->textureMapping(n);
//        glm::vec3 tex_col = CImage::getTexel(hit_obj->texture, uv.x, uv.y);
//        out.col = out.col * tex_col;
//
//    }

    ray.pos = {0,0,0};
    ray.dir = {0.5f, 0.5f, 0.0f};
    n = {0,1,0};
    glm::vec3 pos = {0,0,0};
    CRay ray_reflected = CRayTrace::reflectedRay(ray, n, pos);

    /// computes ambient color component



    /// if the surface is reflective

        /// if out.tree >= MAX_RAY_TREE return from function

        /// computes the secondary ray parameters (reflected ray)

        /// recursion



    return true;
}


/// \fn reflectedRay(CRay ray, glm::vec3 n, glm::vec3 pos)
/// \brief Computes parameters of the ray reflected at the surface point with given normal vector.
/// \param ray Input ray.
/// \param n Surface normal vector.
/// \param pos Position of reflection point.
/// \return Reflected ray.
///
CRay CRayTrace::reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos) {
    CRay reflected_ray;
    glm::vec3 v = ray.dir;
    glm::vec3 r = v - (2.0f * glm::dot(v,n) * n);
    reflected_ray.dir = glm::normalize(r);
    reflected_ray.pos = pos;
//    std::cout<<"pos: "<<reflected_ray.pos[0]<< " " << reflected_ray.pos[1]<< " " <<reflected_ray.pos[2]<<std::endl;
//    std::cout<<"dir: "<<reflected_ray.dir[0]<< " " << reflected_ray.dir[1]<< " " <<reflected_ray.dir[2]<<std::endl;
    return reflected_ray;
}

