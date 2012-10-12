#include "mainwindow.h"
#include "ui_mainwindow.h"

// scene
#include "scene.h"

// tracer
#include "raycast.h"
#include "arealighting.h"
#include "whitted.h"
#include "pathtrace.h"
#include "globaltrace.h"

//shapes
#include "primitives/sphere.h"
#include "primitives/axisalignedbox.h"
#include "primitives/opencylinder.h"
#include "primitives/plane.h"
#include "primitives/rectangle.h"
#include "triangles/triangle.h"
#include "compounded/grid.h"
#include "instance.h"
#include "compounded/solidcylinder.h"
#include "part/convexpartcylinder.h"

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
#include "ambientoccluder.h"

//cameras
#include "orthographic.h"
#include "fisheye.h"
#include "pinhole.h"
#include "thinlens.h"

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
    int num_samples = 10000;

    vp.set_hres(600);
    vp.set_vres(600);
    vp.set_samples(num_samples);
    vp.set_max_depth(10);

    background_color = black;

    tracer_ptr = new PathTrace(this);

    Ambient* ambient_ptr = new Ambient;
    ambient_ptr->scale_radiance(0.0);
    set_ambient_light(ambient_ptr);


    Pinhole* pinhole_ptr = new Pinhole;
    pinhole_ptr->set_eye(27.6, 27.4, -80.0);
    pinhole_ptr->set_lookat(27.6, 27.4, 0.0);
    pinhole_ptr->set_view_distance(800);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);


    Point3D p0;
    Vector3D a, b;
    Normal normal;

    // box dimensions

    double width 	= 55.28;   	// x direction
    double height 	= 54.88;  	// y direction
    double depth 	= 55.92;	// z direction


    // the ceiling light - doesn't need samples

    Emissive* emissive_ptr = new Emissive;
    emissive_ptr->set_ce(1, 1, 1);
    emissive_ptr->scale_radiance(120);

    p0 = Point3D(21.3, height - 0.001, 22.7);
    a = Vector3D(0.0, 0.0, 10.5);
    b = Vector3D(13.0, 0.0, 0.0);
    normal = Normal(0.0, -1.0, 0.0);
    Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
    light_ptr->set_material(emissive_ptr);
    add_object(light_ptr);


    // left wall

    Matte* matte_ptr1 = new Matte;
    matte_ptr1->set_ka(0.0);
    matte_ptr1->set_kd(0.6);
    matte_ptr1->set_cd(0.57, 0.025, 0.025);	 // red
    matte_ptr1->set_sampler(new MultiJittered(num_samples));

    p0 = Point3D(width, 0.0, 0.0);
    a = Vector3D(0.0, 0.0, depth);
    b = Vector3D(0.0, height, 0.0);
    normal = Normal(-1.0, 0.0, 0.0);
    Rectangle* left_wall_ptr = new Rectangle(p0, a, b, normal);
    left_wall_ptr->set_material(matte_ptr1);
    add_object(left_wall_ptr);


    // right wall

    Matte* matte_ptr2 = new Matte;
    matte_ptr2->set_ka(0.0);
    matte_ptr2->set_kd(0.6);
    matte_ptr2->set_cd(0.37, 0.59, 0.2);	 // green   from Photoshop
    matte_ptr2->set_sampler(new MultiJittered(num_samples));

    p0 = Point3D(0.0, 0.0, 0.0);
    a = Vector3D(0.0, 0.0, depth);
    b = Vector3D(0.0, height, 0.0);
    normal = Normal(1.0, 0.0, 0.0);
    Rectangle* right_wall_ptr = new Rectangle(p0, a, b, normal);
    right_wall_ptr->set_material(matte_ptr2);
    add_object(right_wall_ptr);


    // back wall

    Matte* matte_ptr3 = new Matte;
    matte_ptr3->set_ka(0.0);
    matte_ptr3->set_kd(0.6);
    matte_ptr3->set_cd(1.0, 0.93, 0.7);
    matte_ptr3->set_sampler(new MultiJittered(num_samples));

    p0 = Point3D(0.0, 0.0, depth);
    a = Vector3D(width, 0.0, 0.0);
    b = Vector3D(0.0, height, 0.0);
    normal = Normal(0.0, 0.0, -1.0);
    Rectangle* back_wall_ptr = new Rectangle(p0, a, b, normal);
    back_wall_ptr->set_material(matte_ptr3);
    add_object(back_wall_ptr);


    // floor

    p0 = Point3D(0.0, 0.0, 0.0);
    a = Vector3D(0.0, 0.0, depth);
    b = Vector3D(width, 0.0, 0.0);
    normal = Normal(0.0, 1.0, 0.0);
    Rectangle* floor_ptr = new Rectangle(p0, a, b, normal);
    floor_ptr->set_material(matte_ptr3->clone());
    add_object(floor_ptr);


    // ceiling

    p0 = Point3D(0.0, height, 0.0);
    a = Vector3D(0.0, 0.0, depth);
    b = Vector3D(width, 0.0, 0.0);
    normal = Normal(0.0, -1.0, 0.0);
    Rectangle* ceiling_ptr = new Rectangle(p0, a, b, normal);
    ceiling_ptr->set_material(matte_ptr3->clone());
    add_object(ceiling_ptr);


    // the two boxes defined as 5 rectangles each

    // short box

    // top

    p0 = Point3D(13.0, 16.5, 6.5);
    a = Vector3D(-4.8, 0.0, 16.0);
    b = Vector3D(16.0, 0.0, 4.9);
    normal = Normal(0.0, 1.0, 0.0);
    Rectangle* short_top_ptr = new Rectangle(p0, a, b, normal);
    short_top_ptr->set_material(matte_ptr3->clone());
    add_object(short_top_ptr);


    // side 1

    p0 = Point3D(13.0, 0.0, 6.5);
    a = Vector3D(-4.8, 0.0, 16.0);
    b = Vector3D(0.0, 16.5, 0.0);
    Rectangle* short_side_ptr1 = new Rectangle(p0, a, b);
    short_side_ptr1->set_material(matte_ptr3->clone());
    add_object(short_side_ptr1);


    // side 2

    p0 = Point3D(8.2, 0.0, 22.5);
    a = Vector3D(15.8, 0.0, 4.7);
    Rectangle* short_side_ptr2 = new Rectangle(p0, a, b);
    short_side_ptr2->set_material(matte_ptr3->clone());
    add_object(short_side_ptr2);


    // side 3

    p0 = Point3D(24.2, 0.0, 27.4);
    a = Vector3D(4.8, 0.0, -16.0);
    Rectangle* short_side_ptr3 = new Rectangle(p0, a, b);
    short_side_ptr3->set_material(matte_ptr3->clone());
    add_object(short_side_ptr3);


    // side 4

    p0 = Point3D(29.0, 0.0, 11.4);
    a = Vector3D(-16.0, 0.0, -4.9);
    Rectangle* short_side_ptr4 = new Rectangle(p0, a, b);
    short_side_ptr4->set_material(matte_ptr3->clone());
    add_object(short_side_ptr4);




    // tall box

    // top

    p0 = Point3D(42.3, 33.0, 24.7);
    a = Vector3D(-15.8, 0.0, 4.9);
    b = Vector3D(4.9, 0.0, 15.9);
    normal = Normal(0.0, 1.0, 0.0);
    Rectangle* tall_top_ptr = new Rectangle(p0, a, b, normal);
    tall_top_ptr->set_material(matte_ptr3->clone());
    add_object(tall_top_ptr);


    // side 1

    p0 = Point3D(42.3, 0.0, 24.7);
    a = Vector3D(-15.8, 0.0, 4.9);
    b = Vector3D(0.0, 33.0, 0.0);
    Rectangle* tall_side_ptr1 = new Rectangle(p0, a, b);
    tall_side_ptr1->set_material(matte_ptr3->clone());
    add_object(tall_side_ptr1);


    // side 2

    p0 = Point3D(26.5, 0.0, 29.6);
    a = Vector3D(4.9, 0.0, 15.9);
    Rectangle* tall_side_ptr2 = new Rectangle(p0, a, b);
    tall_side_ptr2->set_material(matte_ptr3->clone());
    add_object(tall_side_ptr2);


    // side 3

    p0 = Point3D(31.4, 0.0, 45.5);
    a = Vector3D(15.8, 0.0, -4.9);
    Rectangle* tall_side_ptr3 = new Rectangle(p0, a, b);
    tall_side_ptr3->set_material(matte_ptr3->clone());
    add_object(tall_side_ptr3);


    // side 4

    p0 = Point3D(47.2, 0.0, 40.6);
    a = Vector3D(-4.9, 0.0, -15.9);
    Rectangle* tall_side_ptr4 = new Rectangle(p0, a, b);
    tall_side_ptr4->set_material(matte_ptr3->clone());
    add_object(tall_side_ptr4);

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
    QString filename = QString("res.png");
    img.save(filename);
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
