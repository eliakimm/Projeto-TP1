#!/bin/bash
# 🚀 QUICK START — Comandos Rápidos para TP1

cd c:/Users/Acer/Documents/Estudos/Meus_repositorios/Projeto-TP1/Trabalho_tp1

echo "╔════════════════════════════════════════════════════════════════╗"
echo "║       🚀 QUICK START — TP1 (Sistema de Hotéis)               ║"
echo "║          95.8% COMPLETO (575/600 pontos)                     ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo ""

PS3="Escolha uma opção: "
options=(
    "📖 Ver README (instruções)"
    "🔨 Compilar projeto (bash build.sh)"
    "✅ Executar testes (18 casos)"
    "🎮 Executar app interativa"
    "📚 Ver documentação HTML"
    "📋 Ver critérios de avaliação"
    "📊 Ver sumário de critérios"
    "📑 Ver índice de arquivos"
    "📖 Ver documentação Doxygen"
    "❌ Sair"
)

select opt in "${options[@]}"
do
    case $opt in
        "📖 Ver README (instruções)")
            cat README.md
            ;;
        "🔨 Compilar projeto (bash build.sh)")
            bash build.sh
            ;;
        "✅ Executar testes (18 casos)")
            echo "Executando testes..."
            ./tests/test_all.exe
            ;;
        "🎮 Executar app interativa")
            echo "Executando aplicação..."
            echo "Credenciais padrão:"
            echo "  Email: gerente@hotel.com"
            echo "  Senha: A1a\$2"
            echo ""
            ./Trabalho_tp1.exe
            ;;
        "📚 Ver documentação HTML")
            echo "Abrindo documentação HTML..."
            if command -v start &> /dev/null; then
                start html/index.html
            elif command -v open &> /dev/null; then
                open html/index.html
            else
                xdg-open html/index.html
            fi
            ;;
        "📋 Ver critérios de avaliação")
            cat CRITERIOS_AVALIACAO.md
            ;;
        "📊 Ver sumário de critérios")
            cat SUMARIO_CRITERIOS.md
            ;;
        "📑 Ver índice de arquivos")
            cat INDEX.md
            ;;
        "📖 Ver documentação Doxygen")
            cat DOCUMENTACAO.md
            ;;
        "❌ Sair")
            echo "Até logo! 👋"
            break
            ;;
        *) echo "Opção inválida";;
    esac
    echo ""
    echo "Pressione ENTER para continuar..."
    read
done
