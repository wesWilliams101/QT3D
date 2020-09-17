#include <QGuiApplication>
#include <QColor>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DExtras/QOrbitCameraController>

Qt3DCore::QEntity *createScene()
{
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    // Material
    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(rootEntity);
    material->setAmbient(QColor("#0000ff"));
    material->setShininess(300.0);

    // STL Model
    Qt3DCore::QEntity *stlEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *stlMesh = new Qt3DRender::QMesh(stlEntity);
    stlMesh->setSource(QUrl::fromLocalFile("D:/Engine-Benchmark.stl"));  // pick any local .stl file

    Qt3DCore::QTransform *stlTransform = new Qt3DCore::QTransform(stlEntity);
    stlTransform->setScale3D(QVector3D(.35, .35, .35));
    stlTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0.5), 40.0f));
    stlTransform->setTranslation(QVector3D(2.0,5.0,0));

    stlEntity->addComponent(stlMesh);
    stlEntity->addComponent(stlTransform);
    stlEntity->addComponent(material);

    return rootEntity;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;

    Qt3DCore::QEntity *scene = createScene();

    // Camera
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(scene);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);

    view.setRootEntity(scene);

    view.show();

    return app.exec();
}
