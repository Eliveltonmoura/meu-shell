#!/bin/bash

# Teste automatizado para o shell 238p
# Certifique-se de que o binário sh238p já foi compilado (make all)

BIN=./sh238p
TMP_OUT="out.txt"
TMP_ERR="err.txt"

echo "=== Iniciando testes do shell 238p ==="

# Teste 1 — execução simples
echo "ls" | $BIN > $TMP_OUT
if grep -q "sh238p" "$TMP_OUT"; then
  echo "[OK] Teste 1: comando ls executado com sucesso"
else
  echo "[FALHOU] Teste 1: ls não produziu saída esperada"
fi

# Teste 2 — comando com argumento
echo "/bin/echo Hello World" | $BIN > $TMP_OUT
if grep -q "Hello World" "$TMP_OUT"; then
  echo "[OK] Teste 2: echo com argumento"
else
  echo "[FALHOU] Teste 2: echo com argumento"
fi

# Teste 3 — redirecionamento de saída
echo "echo 238P > test_output.txt" | $BIN
if [ "$(cat test_output.txt)" = "238P" ]; then
  echo "[OK] Teste 3: redirecionamento de saída >"
else
  echo "[FALHOU] Teste 3: redirecionamento > não funcionou"
fi
rm -f test_output.txt

# Teste 4 — redirecionamento de entrada
echo "238P is cool" > test_input.txt
echo "cat < test_input.txt" | $BIN > $TMP_OUT
if grep -q "238P is cool" "$TMP_OUT"; then
  echo "[OK] Teste 4: redirecionamento de entrada <"
else
  echo "[FALHOU] Teste 4: redirecionamento < não funcionou"
fi
rm -f test_input.txt

# Teste 5 — comando interno cd
echo "cd .." | $BIN
if [ $? -eq 0 ]; then
  echo "[OK] Teste 5: comando interno cd executado"
else
  echo "[FALHOU] Teste 5: comando cd falhou"
fi

# Teste 6 — comando history
(echo "ls"; echo "history"; echo "exit") | $BIN > $TMP_OUT
if grep -q "history" "$TMP_OUT"; then
  echo "[OK] Teste 6: comando history funcionando"
else
  echo "[FALHOU] Teste 6: history não listou comandos"
fi

# Teste 7 — comando exit
echo "exit" | $BIN > $TMP_OUT
if [ $? -eq 0 ]; then
  echo "[OK] Teste 7: comando exit encerra shell"
else
  echo "[FALHOU] Teste 7: exit não funcionou"
fi

rm -f "$TMP_OUT" "$TMP_ERR"
echo "=== Testes concluídos ==="
