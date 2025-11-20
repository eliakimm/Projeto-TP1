#!/bin/bash

# Build script para Trabalho TP1

echo "🔨 Compilando projeto..."

# Compilar aplicação principal
g++ -Wall -fexceptions -std=c++17 *.cpp -o Trabalho_tp1.exe
if [ $? -eq 0 ]; then
    echo "✅ Aplicação compilada: Trabalho_tp1.exe"
else
    echo "❌ Erro na compilação da aplicação"
    exit 1
fi

# Compilar testes de integração
g++ -Wall -fexceptions -std=c++17 *.cpp tests/test_all.cpp -o tests/test_all.exe
if [ $? -eq 0 ]; then
    echo "✅ Testes de integração compilados: tests/test_all.exe"
else
    echo "❌ Erro na compilação dos testes de integração"
    exit 1
fi

# Compilar testes CRUD
g++ -Wall -fexceptions -std=c++17 *.cpp tests/test_crud.cpp -o tests/test_crud.exe
if [ $? -eq 0 ]; then
    echo "✅ Testes CRUD compilados: tests/test_crud.exe"
else
    echo "❌ Erro na compilação dos testes CRUD"
    exit 1
fi

echo ""
echo "✨ Build completo! Opções:"
echo "  • Executar app:      ./Trabalho_tp1.exe"
echo "  • Testar tudo:       ./tests/test_all.exe"
echo "  • Testar CRUD:       ./tests/test_crud.exe"
