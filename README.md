Utilice vcpkg para usar CGAL. Programé y compilé en Windows usando Visual Studio 2022.
## Instalar CGAL
1. Descargar vcpkg
2. Añadir a Path
3. ```vcpkg install cgal```
4. Esperar mucho rato

## CMake
Ejecutar CMake en carpeta build con la flag -DCMAKE_TOOLCHAIN_BUILD=<directorio_principal_vcpkg>/scripts/buildsystems/vcpkg.cmake

También hay que cambiar esta variable en el archivo CMakeLists.txt

En mi caso:

`cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/Users/user/Desktop/Repositorios/vcpkg/scripts/buildsystems/vcpkg.cmake`

## Compilación
Yo ocupé Windows, asi que, luego de ejecutar CMake, abrí la solución desde Visual Studio 2022 y compile normalmente. En este punto todo debería funcionar.
