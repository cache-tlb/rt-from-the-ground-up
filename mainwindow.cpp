#include "mainwindow.h"
#include "ui_mainwindow.h"

// scene
#include "scene.h"

// tracer
#include "raycast.h"
#include "arealighting.h"
#include "whitted.h"

//shapes
#include "primitives/sphere.h"
#include "primitives/axisalignedbox.h"
#include "primitives/opencylinder.h"
#include "primitives/plane.h"
#include "primitives/rectangle.h"
#include "triangles/triangle.h"
#include "compounded/grid.h"
#include "instance.h"

//materials
#include "matte.h"
#include "phong.h"
#include "reflective.h"
#include "emissive.h"
#include "glossyreflector.h"
#include "sv_matte.h"
#include "image.h"

//lights
#include "directional.h"
#include "arealight.h"
#include "pointlight.h"

//cameras
#include "orthographic.h"
#include "pinhole.h"

// texture
#include "imagetexture.h"

//sampler
#include "multijittered.h"

//mapping
#include "sphericalmap.h"

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
using namespace std;

void Scene::build(void)
{
    int num_samples = 16;

        vp.set_hres(700);
        vp.set_vres(700);
        vp.set_samples(num_samples);

        background_color = black;

        tracer_ptr = new RayCast(this);

        Pinhole* camera_ptr = new Pinhole;
        camera_ptr->set_eye(0, 0, 65);
        camera_ptr->set_lookat(0.0);
        camera_ptr->set_view_distance(21000.0);
        camera_ptr->compute_uvw();
        set_camera(camera_ptr);


        Directional* light_ptr = new Directional;
        light_ptr->set_direction(-0.25, 0.4, 1);
        light_ptr->scale_radiance(2.5);
        add_light(light_ptr);


        // image:

        Image* image_ptr = new Image;
    //	image_ptr->read_ppm_file("EarthLowRes.ppm");
        image_ptr->read_image("F:\\Code\\temp\\rendering-code\\wxraytracer\\TextureFiles\\jpg\\EarthHighRes.jpg");


        // mapping:

        SphericalMap* map_ptr = new SphericalMap;


        // image based texture:

        ImageTexture* texture_ptr = new ImageTexture;
        texture_ptr->set_image(image_ptr);
        texture_ptr->set_mapping(map_ptr);


        // textured material:

        SV_Matte* sv_matte_ptr = new SV_Matte;
        sv_matte_ptr->set_ka(0.2);
        sv_matte_ptr->set_kd(0.8);
        sv_matte_ptr->set_cd(texture_ptr);


        // generic sphere:

        Sphere*	sphere_ptr = new Sphere;
        sphere_ptr->set_material(sv_matte_ptr);


        // rotated sphere

        Instance* earth_ptr = new Instance(sphere_ptr);
        earth_ptr->rotate_y(60);
        add_object(earth_ptr);


    render_res = new RGBColor[vp.hres*vp.vres];
}

void MainWindow::test()
{
    Image* image_ptr = new Image;
        image_ptr->read_image("F:\\Code\\temp\\rendering-code\\wxraytracer\\TextureFiles\\jpg\\Sarah.jpg");

        int row = image_ptr->get_vres(), col = image_ptr->get_hres();

        IplImage *img = cvCreateImage(cvSize(col,row),8,3);
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                RGBColor c = image_ptr->get_color(row - 1 - i,j);
                CvScalar s = cvScalar(c.b * 255.0, c.g * 255.0, c.r * 255.0);
                cvSet2D(img,i,j,s);
            }
        }
        cvShowImage("test",img);
        cvWaitKey();
}

void MainWindow::render()
{
    Scene scene;
    scene.build();
    //scene.render_scene();
    scene.camera_ptr->render_scene(scene);

    int row = scene.vp.vres, col = scene.vp.hres;
    QImage img(QSize(col,row),QImage::Format_RGB32);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            RGBColor color = scene.render_res[(row - 1 - i)*col+j];
            img.setPixel(j,i,qRgb(color.r,color.g,color.b));
        }
    }

    QGraphicsScene *UIscene = ui->graphicsView->scene();
    UIscene->clear();
    UIscene->addPixmap(QPixmap::fromImage(img));
    return;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    QGraphicsScene *scene = ui->graphicsView->scene();
    if(!scene){
        scene = new QGraphicsScene;
        ui->graphicsView->setScene(scene);
    }
    render();
}

MainWindow::~MainWindow()
{
    delete ui;
}
