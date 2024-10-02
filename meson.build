project('TinyMesh', 'cpp')

qt_moc = import('qt6')
qt6 = dependency(
    'qt6',
    modules: ['Core', 'Widgets', 'Gui', 'OpenGL', 'OpenGLWidgets'],
)
glew = dependency('glew')

tinymesh_sources = files(
    'AppTinyMesh/Source/box.cpp',
    'AppTinyMesh/Source/camera.cpp',
    'AppTinyMesh/Source/evector.cpp',
    'AppTinyMesh/Source/implicits.cpp',
    'AppTinyMesh/Source/main.cpp',
    'AppTinyMesh/Source/mesh-widget.cpp',
    'AppTinyMesh/Source/mesh.cpp',
    'AppTinyMesh/Source/meshcolor.cpp',
    'AppTinyMesh/Source/qtemainwindow.cpp',
    'AppTinyMesh/Source/ray.cpp',
    'AppTinyMesh/Source/shader-api.cpp',
    'AppTinyMesh/Source/triangle.cpp', 
    'AppTinyMesh/Source/surface.cpp', 
    'AppTinyMesh/Source/bezier.cpp', 
)
tinymesh_headers = include_directories('AppTinyMesh/Include')

tinymesh_moc_files = qt_moc.compile_moc(
    headers: files('AppTinyMesh/Include/qte.h', 'AppTinyMesh/Include/realtime.h'),
)
tinymesh_ui = qt_moc.compile_ui(sources: files('AppTinyMesh/UI/interface.ui'))

executable(
    'TinyMesh',
    tinymesh_sources + tinymesh_moc_files + tinymesh_ui,
    include_directories: [tinymesh_headers, include_directories('Libs')],
    dependencies: [qt6, glew],
)