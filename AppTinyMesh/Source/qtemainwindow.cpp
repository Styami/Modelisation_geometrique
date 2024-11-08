#include "AppTinyMesh/Include/bezier.hpp"
#include "AppTinyMesh/Include/deformation.hpp"
#include "mathematics.h"
#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"
#include <chrono>

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;

	// QSurfaceFormat format;
	// format.setDepthBufferSize(24);
	// format.setStencilBufferSize(8);
	// format.setVersion(4, 3);
	// format.setProfile(QSurfaceFormat::CoreProfile);
	// meshWidget->setFormat(format);

	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	Bezier bez(100, 100, 7, 7); //FIXME : Faire en sorte que le fonction soit templatée pour les points de contrôles
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "temps de création de la surface de bézier : " << 
				std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()
				<< "µs"
				<< std::endl;
	Mesh bezMesh = Mesh(bez.get_mesh());
	begin = std::chrono::high_resolution_clock::now();
  	bezMesh = deformation_local(bezMesh, Vector(5, 2, 2), 20);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "temps de la déformation locale : " << 
			std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()
			<< "µs"
			<< std::endl;
	bezMesh = deformation_forme_libre(bezMesh);
	std::vector<Color> cols(bezMesh.Vertexes());
	// cols.resize(bezMesh.Vertexes());//boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

	meshColor = MeshColor(bezMesh, cols, bezMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::SphereImplicitExample()
{
	
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	AnalyticScalarField implicit;
	Mesh implicitMesh;
	implicit.Polygonize(200, implicitMesh, Box(4.0));
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "temps de création de la scène : " << 
		std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()
		<< "ms"
		<< std::endl;
	std::vector<Color> cols;

	cols.resize(implicitMesh.Vertexes());

	for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(0.8, 0.8, 0.8);

	meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
