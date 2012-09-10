#include "mainwindow.h"
#include "ui_mainwindow.h"

// scene
#include "scene.h"

// tracer
#include "raycast.h"
#include "arealighting.h"
#include "whitted.h"
#include "pathtrace.h"

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
    int num_samples = 64;

    vp.set_hres(400);
    vp.set_vres(400);
    vp.set_samples(num_samples);

    tracer_ptr = new RayCast(this);

    MultiJittered* sampler_ptr = new MultiJittered(num_samples);

    AmbientOccluder* acl_ptr = new AmbientOccluder;
//  acl_ptr->set_min_amount(1.0);    	// for Figure 17.12(a)
    acl_ptr->set_min_amount(0.25);		// for Figure 17.12(b)
//	acl_ptr->set_min_amount(0.0);		// for Figure 17.12(c)
    acl_ptr->set_sampler(sampler_ptr);
    set_ambient_light(acl_ptr);

    Pinhole* pinhole_ptr = new Pinhole;

    // for regular view

    pinhole_ptr->set_eye(20, 10, 40);
    pinhole_ptr->set_lookat(-0.025, 0.11, 0.0);
    pinhole_ptr->set_view_distance(70000);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);


    Directional* light_ptr1 = new Directional;
    light_ptr1->set_direction(20, 40, 20);
    light_ptr1->scale_radiance(2.5);
    light_ptr1->set_shadows(true);
    add_light(light_ptr1);


    float ka = 0.5;		// used for all materials

    Matte* matte_ptr1 = new Matte;
    matte_ptr1->set_ka(ka);
    matte_ptr1->set_kd(0.5);
    matte_ptr1->set_cd(0.5, 0.75, 1);   // pale blue for bunny


    char* file_name = "F:\\Code\\temp\\rendering-code\\wxraytracer\\PLYFiles\\Stanford Bunny\\BunnyMedium.ply"; 	// 10000 triangles - needs the normals reversed

    Grid* bunny_ptr = new Grid;
//    bunny_ptr->reverse_mesh_normals();				// only required for the Bunny10K.ply file
//	bunny_ptr->read_flat_triangles(file_name);		// read PLY file
    bunny_ptr->read_smooth_triangles(file_name);	// read PLY file
    bunny_ptr->set_material(matte_ptr1);
    bunny_ptr->setup_cells();

    Instance* rotated_bunny_ptr = new Instance(bunny_ptr);
    rotated_bunny_ptr->set_material(matte_ptr1);
    rotated_bunny_ptr->rotate_y(40);
    add_object(rotated_bunny_ptr);


    // rectangle parameters

    Point3D p0(-0.13, 0.033, -0.1);  	// common corner
    float height = 0.25;  				// y direction
    float width = 0.45;  				// x direction
    float depth = 0.45;   				// z direction

    // horizontal rectangle

    Matte* matte_ptr2 = new Matte;
    matte_ptr2->set_ka(ka);
    matte_ptr2->set_kd(0.5);
    matte_ptr2->set_cd(white);

    Rectangle* rectangle_ptr1 = new Rectangle(p0, Vector3D(0, 0,depth), Vector3D(width, 0, 0));
    rectangle_ptr1->set_material(matte_ptr2);
    add_object(rectangle_ptr1);

    // rectangle perpendicular to x axis

    Matte* matte_ptr3 = new Matte;
    matte_ptr3->set_ka(ka);
    matte_ptr3->set_kd(0.75);
    matte_ptr3->set_cd(0.5, 1, 0.75);

    Rectangle* rectangle_ptr2 = new Rectangle(p0, Vector3D(0, height, 0), Vector3D(0, 0, depth));
    rectangle_ptr2->set_material(matte_ptr3);
    add_object(rectangle_ptr2);

    // rectangle perpendicular to w axis

    Matte* matte_ptr4 = new Matte;
    matte_ptr4->set_ka(ka);
    matte_ptr4->set_kd(0.5);
    matte_ptr4->set_cd(1, 1, 0.5);

    Rectangle* rectangle_ptr3 = new Rectangle(p0, Vector3D(width, 0, 0), Vector3D(0, height, 0));
    rectangle_ptr3->set_material(matte_ptr4);
    add_object(rectangle_ptr3);


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
