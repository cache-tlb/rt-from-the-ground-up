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
#include "transparent.h"
#include "dielectric.h"

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
#include "planechecker.h"

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
    int num_samples = 25;

    vp.set_hres(600);
    vp.set_vres(600);
    vp.set_samples(num_samples);
    vp.set_max_depth(6);

    background_color = RGBColor(0.0, 0.13, 0.1);

    tracer_ptr = new Whitted(this);

    Ambient* ambient_ptr = new Ambient;
    ambient_ptr->set_color(0.45, 0.5, 0.45);
    ambient_ptr->scale_radiance(0.25);
    set_ambient_light(ambient_ptr);


    Pinhole* pinhole_ptr = new Pinhole;
    pinhole_ptr->set_eye(0, 0, 10);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(2800.0);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);


    Directional* light_ptr1 = new Directional;
    light_ptr1->set_direction(10, 10, 10);
    light_ptr1->scale_radiance(7.0);
    light_ptr1->set_shadows(false);
    add_light(light_ptr1);

    Directional* light_ptr2 = new Directional;
    light_ptr2->set_direction(-1, 0, 0);
    light_ptr2->scale_radiance(7.0);
    light_ptr2->set_shadows(false);
    add_light(light_ptr2);


    // transparent unit sphere at the origin

    Dielectric* dielectric_ptr = new Dielectric;
    dielectric_ptr->set_eta_in(1.5);		// glass
    dielectric_ptr->set_eta_out(1.0);		// air
    dielectric_ptr->set_cf_in(white);
    dielectric_ptr->set_cf_out(white);

    Sphere* sphere_ptr1 = new Sphere;
    sphere_ptr1->set_material(dielectric_ptr);


    // red reflective sphere inside the transparent sphere

    // the Reflective parameters below are for the reflective sphere in a glass sphere
    // they are too dark for the diamond sphere because of the etas

    Reflective*	reflective_ptr = new Reflective;
    reflective_ptr->set_ka(0.1);
    reflective_ptr->set_kd(0.7);
    reflective_ptr->set_cd(red);
    reflective_ptr->set_ks(0.3);
    reflective_ptr->set_exp(200.0);
    reflective_ptr->set_kr(0.5);
    reflective_ptr->set_cr(white);

    double radius = 0.1;
    double distance = 0.8;   // from center of transparent sphere

    Sphere* sphere_ptr2 = new Sphere(Point3D(0, 0, distance), radius);
    sphere_ptr2->set_material(reflective_ptr);

    // store the spheres in a compound object

    Compound* spheres_ptr = new Compound;
    spheres_ptr->add_object(sphere_ptr1);
    spheres_ptr->add_object(sphere_ptr2);

    // now store compound object in an instance so that we can rotate it

    Instance* rotated_spheres_ptr = new Instance(spheres_ptr);
//  rotated_spheres_ptr->rotate_y(0.0);		// for Figure 28.28(a)
//	rotated_spheres_ptr->rotate_y(120.0);  	// for Figure 28.28(b)
//	rotated_spheres_ptr->rotate_y(162.0);  	// for Figure 28.28(c)
    rotated_spheres_ptr->rotate_y(164.0);  	// for Figure 28.28(d)
    add_object(rotated_spheres_ptr);


    // ground plane

    Checker3D* checker3D_ptr = new Checker3D;
    checker3D_ptr->set_size(50.0);
    checker3D_ptr->set_color1(0.5);
    checker3D_ptr->set_color2(1.0);

    SV_Matte* sv_matte_ptr = new SV_Matte;
    sv_matte_ptr->set_ka(0.25);
    sv_matte_ptr->set_kd(0.5);
    sv_matte_ptr->set_cd(checker3D_ptr);

    Plane* plane_ptr = new Plane(Point3D(0, -40.5, 0), Normal(0, 1, 0));
    plane_ptr->set_material(sv_matte_ptr);
    add_object(plane_ptr);


    render_res = new RGBColor[vp.hres*vp.vres];
}

void MainWindow::test()
{
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
    marble_ptr->set_perturbation(8.0);		// for Figure 31.33(b)
    //marble_ptr->set_perturbation(30.0);		// for Figure 31.33(c)

    int row = 600, col = 600;
    QImage img(QSize(col,row),QImage::Format_RGB32);
    Scene s;
    ShadeRec sr(s);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            sr.local_hit_point.x = (double)j/col*10;
            sr.local_hit_point.y = (double)i/row*10 + (double)j/col*5;
            RGBColor color = marble_ptr->get_color(sr);
            img.setPixel(j,i,qRgb(color.r*255,color.g*255,color.b*255));
        }
    }

    QGraphicsScene *UIscene = ui->graphicsView->scene();
    UIscene->clear();
    UIscene->addPixmap(QPixmap::fromImage(img));
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
    //test();
}

MainWindow::~MainWindow()
{
    delete ui;
}
