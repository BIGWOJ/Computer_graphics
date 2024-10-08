//////////
///
/// W pliku CScene.cpp zostały przypisane wartości kamery w 2 wariantach
/// W pliku CRayTrace.cpp zostało zaimplementowanie obliczanie parametrów macierzy rzutowania
/// Wspomniane parametry zostały przypisane do macierzy
///
//////////

#include <iostream>


#include "rt.h"

extern void draw_robot();
extern void draw_triangles();
float radian(float kat)
{
    return (kat * 3.14f) / 180;
}

///
int main (int argc, char * const argv[]) {

    //draw_triangles();
    //draw_robot();
    //return 0;

    std::cout << "ray tracing ... \n";

    CScene scene;
    scene.create(); // defines sample scene parameters
    if(scene.cam.width == 0) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return -1;
    }

    CRayTrace rt;
    CRay ray;
    COutput results;

    /// computes primary ray matrix
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    std::cout << "Camera projection matrix:" << std::endl;
    PRINT_MAT3(ray_matrix);

    /// computes ray direction for sample pixel positions
    // ...

//WYZNACZANIE PROMIENI PPIERWOTNYCH

    float fx, fy;

    fx = scene.cam.width/2.0f - 1.0f + 0.5f;
    fy = scene.cam.height/2.0f - 1.0f + 0.5f;
    glm::vec3 wektor (fx, fy, 1.0f);
    ray.dir = glm::normalize(ray_matrix * wektor);
    std::cout << fx << "," << fy << " -> ";
    PRINT_VEC3("ray.dir: ", ray.dir);

    fx = 0.5f;
    fy = 0.5f;
    wektor = {fx, fy, 1.0f};
    ray.dir = glm::normalize(ray_matrix * wektor);
    std::cout << fx << "," << fy << " -> ";
    PRINT_VEC3("ray.dir: ", ray.dir);

    fx = scene.cam.width/2.0f - 1.0f + 0.5f;
    fy = 0.5f;
    wektor = {fx, fy, 1.0f};
    ray.dir = glm::normalize(ray_matrix * wektor);
    std::cout << fx << "," << fy << " -> ";
    PRINT_VEC3("ray.dir: ", ray.dir);

    fx = 0.5f;
    fy = scene.cam.height/2.0f - 1.0f + 0.5f;
    wektor = {fx, fy, 1.0f};
    ray.dir = glm::normalize(ray_matrix * wektor);
    std::cout << fx << "," << fy << " -> ";
    PRINT_VEC3("ray.dir: ", ray.dir);

    fx = scene.cam.width - 1.0f + 0.5f;
    fy = scene.cam.height - 1.0f + 0.5f;
    wektor = {fx, fy, 1.0f};
    ray.dir = glm::normalize(ray_matrix * wektor);
    std::cout << fx << "," << fy << " -> ";
    PRINT_VEC3("ray.dir: ", ray.dir);



    /// creates raster image object
    CImage image(scene.cam.width, scene.cam.height);

    /// main loop

//Ćwiczenie 6 - dodanie głównej pętli ray tracera, która oblicza kierunkipromienia pierwotnego dla
//promieni przechodzących przez wszystkie piksele obrazu

    for (int j = 0; j < scene.cam.height; j++) {
        for (int i = 0; i < scene.cam.width; i++) {

            /// position of the image point
            /// ...

            float fx = (float) i + 0.5f;
            float fy = (float) j + 0.5f;

            //Ustawienie miejsca kamery oraz kierunku promienia
            wektor = {fx, fy, 1.0f};
            ray.dir = glm::normalize(ray_matrix * wektor);

            //glm::vec3 rgb(0.0f, 0.0f, 0.0f);
            ray.pos = scene.cam.eyep;
            ray.dir = ray_matrix * glm::vec3(fx, fy, 1.0f);
            ray.dir = glm::normalize(ray.dir);

            //x - kolor czerwony
            //rgb.x = (ray.dir.x + 1.0f) / 2.0f;
            //rgb.y = (ray.dir.y + 1.0f)/2.0f;
            //rgb.z = (ray.dir.z + 1.0f)/2.0f;
            //image.setPixel(i,j,rgb);

            //kolor tła
            results.col = {0,0,0};

            results.energy = 1.0f;
            results.tree = 0;
            rt.rayTrace(scene, ray, results);

            if (results.col.x > 1 || results.col.y > 1 || results.col.z > 1)
            {
                results.col = {1,1,1};
            }

            image.setPixel(i,j, results.col);
        }
    }

    image.plotCalibChart();

    cv::imshow("image", image.getImage());
    cv::waitKey();
    image.save("output_image.png", true);

    //Dodanie testowej kuli i obliczenie jej parametru t
//    ray.pos = {0,0,10};
//    ray.dir = {0.3, 0.3, -1};
    //CSphere* sphere2 = new CSphere({0,0,0}, 5);
    //std::cout << "t = " <<  sphere2->intersect(ray);


    /// primary ray
    /// ...



    /// background color
    // results.col = {0,0,0};
    /// secondary ray counter
    // results.tree = 0;
    /// ray energy
    // results.energy = 1.0f;-

    /// rendering
    /// rt.rayTrace(scene, ray, results);

    /// handles pixel over-saturation
//     if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
//        results.col = {1,1,1};
//    }

    /// writes pixel to output image
    //image.setPixel(i, j, results.rgb);



    /// writes image to disk file with gamma correction
//    image.save("output_image.png", false);
//
//    cv::imshow("image", image.getImage());
//    cv::waitKey();

    std::cout << std::endl << std::endl;
    return 0;
}


/// Draws two trianges
void draw_triangles() {

    CImage img(1000, 1000);

    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green

    // draw circle
    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;
    img.drawCircle(pp, radius, color1);

    // triangle vertices
    glm::vec3 pp0(0.4, 0.3, 1);
    glm::vec3 pp1(-0.4, 0.3, 1);
    glm::vec3 pp2(0.4, -0.3, 1);

    // draws triangle in 2D
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp0, color1);

    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;

    // draws triangle after translation
    img.drawLine(pp0, pp1, color2);
    img.drawLine(pp1, pp2, color2);
    img.drawLine(pp2, pp0, color2);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();

}

/// Draws robot.
void draw_robot() {

    CImage img(1000, 1000);

    glm::vec3 color(1, 0.7, 0.1);
    glm::vec3 pp(0,0.40,1);

//GŁOWA

    float radius = 0.1f;
    img.drawCircle(pp, radius, color);

//TUŁÓW

    glm::vec3 cialo0(0.15, -0.25, 1);
    glm::vec3 cialo1(0.15, 0.25, 1);
    glm::vec3 cialo2(-0.15, 0.25, 1);
    glm::vec3 cialo3(-0.15, -0.25, 1);

    img.drawLine(cialo0, cialo1, color);
    img.drawLine(cialo1, cialo2, color);
    img.drawLine(cialo2,cialo3, color);
    img.drawLine(cialo3, cialo0, color);

// PRAWA NOGA

    float tX = -0.30f;
    float tY = -0.45f;
    //Napisałem dodatkową funkcję radian() do szybszego obliczania radianu na podstawie kątu. Jest na samym początku kodu.
    float kat = radian(35);

    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}};
    glm::mat3x3 mObr {{cos(kat), -sin(kat), 0}, {sin(kat), cos(kat), 0}, {0,0,1} };
    glm::mat3x3 mSkal {{0.35,0,0}, {0,0.70,0}, {0,0,1}};
    glm::vec3 pp0, pp1, pp2, pp3;

    pp0 = mTrans * mObr * mSkal * cialo0;
    pp1 = mTrans * mObr * mSkal * cialo1;
    pp2 = mTrans * mObr * mSkal * cialo2;
    pp3 = mTrans * mObr * mSkal * cialo3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);

// LEWA NOGA

    tX = 0.0f;
    tY = 0.0f;
    kat = radian(-67);

    mObr = {{cos(kat), -sin(kat), 0}, {sin(kat), cos(kat), 0}, {0,0,1} };
    mTrans = {{1,0,0}, {0,1,0}, {tX,tY,1}};

    pp0 = mTrans * mObr * pp0;
    pp1 = mTrans * mObr * pp1;
    pp2 = mTrans * mObr * pp2;
    pp3 = mTrans * mObr * pp3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);

//LEWA RĘKA

    tX = 0.40f;
    tY = 0.195f;
    kat = radian(90);

    mTrans = {{1,0,0}, {0,1,0}, {tX,tY,1}};
    mObr = {{cos(kat), -sin(kat), 0}, {sin(kat), cos(kat), 0}, {0,0,1} };
    mSkal = {{0.35,0,0}, {0,0.70,0}, {0,0,1}};

    pp0 = mTrans * mObr * mSkal * cialo0;
    pp1 = mTrans * mObr * mSkal * cialo1;
    pp2 = mTrans * mObr * mSkal * cialo2;
    pp3 = mTrans * mObr * mSkal * cialo3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2,pp3, color);
    img.drawLine(pp3, pp0, color);

//PRAWA RĘKA

    tX = -0.8f;
    tY = 0.0f;

    mTrans = {{1,0,0}, {0,1,0}, {tX,tY,1}};

    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    pp3 = mTrans * pp3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);


    cv::waitKey();
    cv::imshow("Robot", img.getImage());



}
