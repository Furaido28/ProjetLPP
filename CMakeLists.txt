# Définir la version minimale requise de CMake
cmake_minimum_required(VERSION 3.26)

# Nom du projet
project(Projet C)

# Spécifier la version du standard C à utiliser
set(CMAKE_C_STANDARD 11)

# Ajouter l'exécutable à générer à partir des fichiers sources
add_executable(Projet
    main.c
    store.c
    affichage.c
)
