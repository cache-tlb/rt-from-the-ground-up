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
#include "fisheye.h"
#include "pinhole.h"

// texture
#include "imagetexture.h"
#include "checker3d.h"
#include "tinstance.h"
#include "fbmtexture.h"
#include "wrappedfbmtexture.h"
#include "rampfbmtexture.h"

//sampler
#include "multijittered.h"

//mapping
#include "sphericalmap.h"
#include "rectangularmap.h"
#include "cylindricalmap.h"
#include "lightprobe.h"

//noise
#include "cubicnoise.h"

#include <iostream>
typedef Fisheye FishEye;

void Scene::build(void)
{
    int num_samples = 16;

    vp.set_hres(600);
    vp.set_vres(600);
    vp.set_samples(num_samples);

    background_color = black;
    tracer_ptr = new RayCast(this);

    Pinhole* pinhole_ptr = new Pinhole;
    pinhole_ptr->set_eye(0, 0, 100);
    pinhole_ptr->set_lookat(0.0);
    pinhole_ptr->set_view_distance(5800.0);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);


    PointLight* light_ptr = new PointLight;
    light_ptr->set_location(20, 20, 40);
    light_ptr->scale_radiance(2.5);
    add_light(light_ptr);


    // noise:

    CubicNoise* noise_ptr = new CubicNoise;
    noise_ptr->set_num_octaves(6);
    noise_ptr->set_gain(0.5);
    noise_ptr->set_lacunarity(2.0);

    // ramp image:

    Image* image_ptr = new Image;
    image_ptr->read_image("F:\\Code\\temp\\rendering-code\\wxraytracer\\TextureFiles\\jpg\\BlueMarbleRamp.jpg");

    // marble texture:

    RampFBmTexture* marble_ptr = new RampFBmTexture(image_ptr);
    marble_ptr->set_noise(noise_ptr);
    //marble_ptr->set_perturbation(4.0);		// for Figure 31.33(a)
    //marble_ptr->set_perturbation(8.0);		// for Figure 31.33(b)
    marble_ptr->set_perturbation(30.0);		// for Figure 31.33(c)

    // material:

    SV_Matte* sv_matte_ptr = new SV_Matte;
    sv_matte_ptr->set_ka(0.25);
    sv_matte_ptr->set_kd(0.9);
    sv_matte_ptr->set_cd(marble_ptr);


    Instance* sphere_ptr1 = new Instance(new Sphere(Point3D(0.0), 5.0));
    sphere_ptr1->set_material(sv_matte_ptr);
    sphere_ptr1->rotate_y(180);
    add_object(sphere_ptr1);




    render_res = new RGBColor[vp.hres*vp.vres];
}

void MainWindow::test()
{
    /*Image* image_ptr = new Image;
        image_ptr->read_image("F:\\Code\\temp\\rendering-code\\wxraytracer\\TextureFiles\\jpg\\Lightlace.ppm");

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
        cvWaitKey();*/
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
