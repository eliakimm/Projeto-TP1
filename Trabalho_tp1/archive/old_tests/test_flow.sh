#!/bin/bash
# Script para testar fluxo completo: criar hotel + fazer reserva

cat << 'EOF' | ./app.exe
1
teste@hotel.com
A1b!2
2
Hotel Teste
Rua Teste, 100
+5511999999999
hotelXYZ01
0
3
Eliakim Silva
Samambaia Norte
4111111111111111
hotelXYZ01
125
2
01/02/2025
04/02/2025
reserva001
0
3
EOF
