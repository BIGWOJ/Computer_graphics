//
//  CScene.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///


void CScene::create() {

    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects

    // add camera, light sources, and objects

//USTAWIENIE WARTOŚCI DWÓCH WERSJI KAMER

    //KAMERA 1
    cam.eyep = {0,-4,10};
    cam.lookp = {0,0,0};
    cam.up = {0,1,0};
    cam.fov = 50;
    cam.width = 500;
    cam.height = 400;

    //KAMERA 2
//    cam.eyep = {2,5,10};
//    cam.lookp = {-2,1,0};
//    cam.up = {0,1,0};
//    cam.fov = 50;
//    cam.width = 500;
//    cam.height = 400;

//Teksturowa kula

//    CSphere* sphere = new CSphere({0, 0, 0}, 1.6);
//    sphere->matAmbient = {0.1,0,0};
//    sphere->matDiffuse = {0.6,0,0};
//    sphere->matSpecular = {0.7,0.7,0.7};
//    sphere->matShininess = 50;
//    sphere->reflectance = 0;
//    sphere->isTexture = true;
//    sphere->texture = CImage::createTexture(400,400);
//    objectList.push_back(sphere);
//

    CSphere* sphere = new CSphere({-1, 0, 3}, 0.4);
    sphere->matAmbient = {0,0.1,0};
    sphere->matDiffuse = {0,0.6,0};
    sphere->matSpecular = {0.7,0.7,0.7};
    sphere->matShininess = 30;
    sphere->reflectance = 0;
    objectList.push_back(sphere);

    CSphere* sphere_1 = new CSphere({0, 0, 0}, 1.6);
    sphere_1->matAmbient = {0.1,0,0};
    sphere_1->matDiffuse = {0.6,0,0};
    sphere_1->matSpecular = {0.7,0.7,0.7};
    sphere_1->matShininess = 30;
    sphere_1->reflectance = 0;
    objectList.push_back(sphere_1);

    CSphere* sphere_2 = new CSphere({-3, -2, -2}, 0.6);
    sphere_2->matAmbient = {0,0,0.1};
    sphere_2->matDiffuse = {0,0,0.6};
    sphere_2->matSpecular = {0.7,0.7,0.7};
    sphere_2->matShininess = 30;
    sphere_2->reflectance = 0;
    objectList.push_back(sphere_2);


//Dodanie trójkątów do sceny

    glm::vec3 v0 = {5,5,-5};
    glm::vec3 v1 = {-5,5,-5};
    glm::vec3 v2 = {-5,-5,-5};
    CTriangle* triangle = new CTriangle(v0,v1,v2);
    triangle->matAmbient = {0.1,0.1,0.1};
    triangle->matDiffuse = {0.4,0.4,0.4};
    triangle->matSpecular = {0,0,0};
    triangle->matShininess = 0;
    triangle->reflectance = 1;
    objectList.push_back(triangle);

    v0 = {5,5,-5};
    v1 = {-5,-5,-5};
    v2 = {5,-5,-5};
    CTriangle* triangle_1 = new CTriangle(v0,v1,v2);
    triangle_1->matAmbient = {0.1,0.1,0.1};
    triangle_1->matDiffuse = {0.4,0.4,0.4};
    triangle_1->matSpecular = {0,0,0};
    triangle_1->matShininess = 0;
    triangle_1->reflectance = 1;
    objectList.push_back(triangle_1);

    CLight light1 (glm::vec3 (-3, -2,8));
    light1.color = {0.6, 0.6, 0.6};
    lightList.push_back(light1);

    CLight light2 (glm::vec3 (5,-2,8));
    light2.color = {0.3,0.3,0.3};
    lightList.push_back(light2);


}

