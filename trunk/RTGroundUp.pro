#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T11:39:35
#
#-------------------------------------------------

QT       += core gui

TARGET = RTGroundUp
TEMPLATE = app

INCLUDEPATH += ./utilities \
    ./BRDFs \
    ./cameras \
    ./lights \
    ./materials \
    ./scene \
    ./samplers \
    ./shapes \
    ./tracers \
    ./textures \
    ./mappings \
    ./noises

INCLUDEPATH +=  D:/Library/OpenCV/build/include \
                D:/Library/OpenCV/build/include/opencv

LIBS += D:/Library/OpenCV/build/x86/vc10/lib/*.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    utilities/matrix.cpp \
    utilities/vector3d.cpp \
    utilities/point3d.cpp \
    utilities/normal.cpp \
    utilities/ray.cpp \
    utilities/rgbcolor.cpp \
    utilities/shaderec.cpp \
    shapes/shape.cpp \
    scene/viewplane.cpp \
    scene/scene.cpp \
    tracers/tracer.cpp \
    tracers/raycast.cpp \
    materials/material.cpp \
    BRDFs/brdf.cpp \
    BRDFs/lambertian.cpp \
    materials/matte.cpp \
    lights/light.cpp \
    lights/ambient.cpp \
    lights/directional.cpp \
    utilities/maths.cpp \
    cameras/camera.cpp \
    cameras/pinhole.cpp \
    utilities/point2d.cpp \
    cameras/orthographic.cpp \
    cameras/thinlens.cpp \
    samplers/sampler.cpp \
    cameras/fisheye.cpp \
    lights/pointlight.cpp \
    materials/phong.cpp \
    BRDFs/glossyspecular.cpp \
    samplers/multijittered.cpp \
    utilities/bbox.cpp \
    shapes/instance.cpp \
    shapes/primitives/sphere.cpp \
    shapes/primitives/plane.cpp \
    shapes/primitives/opencylinder.cpp \
    shapes/triangles/triangle.cpp \
    shapes/triangles/smoothtriangle.cpp \
    utilities/mesh.cpp \
    shapes/triangles/meshtriangle.cpp \
    shapes/triangles/smoothmeshtriangle.cpp \
    shapes/triangles/flatmeshtriangle.cpp \
    tracers/whitted.cpp \
    BRDFs/perfectspecular.cpp \
    materials/reflective.cpp \
    shapes/primitives/rectangle.cpp \
    materials/glossyreflector.cpp \
    shapes/primitives/axisalignedbox.cpp \
    lights/arealight.cpp \
    tracers/arealighting.cpp \
    materials/emissive.cpp \
    shapes/compounded/compound.cpp \
    shapes/compounded/grid.cpp \
    utilities/ply.cpp \
    textures/texture.cpp \
    mappings/mapping.cpp \
    mappings/sphericalmap.cpp \
    utilities/image.cpp \
    textures/imagetexture.cpp \
    BRDFs/sv_lambertian.cpp \
    materials/sv_matte.cpp \
    utilities/IO/imageio.cpp \
    mappings/rectangularmap.cpp \
    mappings/cylindricalmap.cpp \
    mappings/lightprobe.cpp \
    shapes/triangles/smoothuvmeshtriangle.cpp \
    shapes/triangles/flatuvmeshtriangle.cpp \
    textures/spherechecker.cpp \
    textures/planechecker.cpp \
    textures/tinstance.cpp \
    textures/checker3d.cpp \
    noises/latticenoise.cpp \
    noises/linearnoise.cpp \
    noises/cubicnoise.cpp \
    textures/fbmtexture.cpp \
    textures/wrappedfbmtexture.cpp \
    textures/rampfbmtexture.cpp

HEADERS  += mainwindow.h \
    utilities/matrix.h \
    utilities/vector3d.h \
    utilities/point3d.h \
    utilities/normal.h \
    utilities/ray.h \
    utilities/rgbcolor.h \
    utilities/maths.h \
    utilities/shaderec.h \
    shapes/shape.h \
    scene/viewplane.h \
    scene/scene.h \
    tracers/tracer.h \
    tracers/raycast.h \
    materials/material.h \
    BRDFs/brdf.h \
    BRDFs/lambertian.h \
    materials/matte.h \
    lights/light.h \
    lights/ambient.h \
    lights/directional.h \
    cameras/camera.h \
    cameras/pinhole.h \
    utilities/constants.h \
    utilities/point2d.h \
    cameras/orthographic.h \
    cameras/thinlens.h \
    samplers/sampler.h \
    cameras/fisheye.h \
    lights/pointlight.h \
    materials/phong.h \
    BRDFs/glossyspecular.h \
    samplers/multijittered.h \
    utilities/bbox.h \
    shapes/instance.h \
    shapes/primitives/sphere.h \
    shapes/primitives/plane.h \
    shapes/primitives/opencylinder.h \
    shapes/triangles/triangle.h \
    shapes/triangles/smoothtriangle.h \
    utilities/mesh.h \
    shapes/triangles/meshtriangle.h \
    shapes/triangles/smoothmeshtriangle.h \
    shapes/triangles/flatmeshtriangle.h \
    tracers/whitted.h \
    BRDFs/perfectspecular.h \
    materials/reflective.h \
    shapes/primitives/rectangle.h \
    materials/glossyreflector.h \
    shapes/primitives/axisalignedbox.h \
    lights/arealight.h \
    tracers/arealighting.h \
    materials/emissive.h \
    shapes/compounded/compound.h \
    shapes/compounded/grid.h \
    utilities/ply.h \
    textures/texture.h \
    mappings/mapping.h \
    mappings/sphericalmap.h \
    utilities/image.h \
    textures/imagetexture.h \
    BRDFs/sv_lambertian.h \
    materials/sv_matte.h \
    utilities/IO/imageio.h \
    mappings/rectangularmap.h \
    mappings/cylindricalmap.h \
    mappings/lightprobe.h \
    shapes/triangles/smoothuvmeshtriangle.h \
    shapes/triangles/flatuvmeshtriangle.h \
    textures/spherechecker.h \
    textures/planechecker.h \
    textures/tinstance.h \
    textures/checker3d.h \
    noises/latticenoise.h \
    noises/linearnoise.h \
    noises/cubicnoise.h \
    textures/fbmtexture.h \
    textures/wrappedfbmtexture.h \
    textures/rampfbmtexture.h

FORMS    += mainwindow.ui
