
# Projeto Vector

O GitHub Classroom (GHC) não oferece um mecanismo integrado para alterar **todos** os repositórios dentro de uma turma automaticamente. Por esse motivo vamos adotar a estratégia de armazenar o repositório com a descrição do projeto externamente.

Dessa forma é possível editar/atualizar a descrição desse projeto e código de suporte, se necessário, sem que seja necessário replicar manualmente essa alteração em cada repositório individual do GHC.

Nesse documento vamos chamar este repositório (derivado do GHC) de repositório **Implementação Projeto Vector**. Já a descrição do projeto e código de suporte está localizada em um _repositório externo_ chamado de [**Descrição Projeto Vector**](https://github.com/selan-ufrn/projeto_vector).

A vantagem desse novo esquema organizacional, separando a descrição do projeto da implementação, é que se for necessário atualizar algo na descrição eu o farei _uma vez_ no repositório **Descrição Projeto Vector** e vocês simplesmente baixam a nova atualização com comandos simples como `git pull`. Para continuarmos a nos beneficiar do sistema de acompanhamento de código e troca de mensagens via _pull request_ com o _branch_ `feedback` ou via a criação de _issues_, você continuará a trabalhar no repositório **Implementação Projeto Vector** que é monitorado pelo GHC. Portanto o procedimento (de integração) a ser seguido é o seguinte:

1. Clone o repositório **Descrição Projeto Vector** na sua máquina.
2. Clone o repositório **Implementação Projeto Vector** (este repo) na sua máquina.
3. Copie o código de suporte (pastas `source` e `data`)  do repo local **Descrição Projeto Vector** para a raiz do repo local **Implementação Projeto Vector**.
3. Quando finalizar (ou se quiser tirar uma dúvida) _"comite"_ e atualize o repositório local **Implementação Projeto Vector**.

Pronto, agora você pode fazer _pull request_ em `feedback` ou abrir alguma _issue_, casa queira tirar dúvidas sobre o projeto.

Ao final desse processo, a implementação completa do projeto terão sido "_comitadas_" para o repo **Implementação Projeto Vector** no GHC. Esse é o repo com seu trabalho que será baixado para avaliação.

## Compilando o Código de Suporte

Primeiramente, certifique-se de ter copiado o código de suporte (`data` e `source`) do repo local **Descrição Projeto Vector** para a raiz do repo local **Implementação Projeto Vector**. Feito isso, para compilar e executar, é só seguir as instruções abaixo.

## Usando `cmake`

A partir da pasta principal do repo local **Implementação Projeto Vector** faça:

```
cmake -S source -B build
cmake --build build
```
Logo após a compilação, para executar os testes gerado use os comandos:

No linux:

```
cd build
make run_tests
```

## Usando compilação manual com g++

É possível compilar o programa "na mão" (i.e. sem o `cmake`) usando o `g++`. Para isso use o comando abaixo a partir da pasta principal do repo local **Implementação Projeto Vector**:

```
mkdir -p build
g++ -Wall -std=c++11 -I source/include -I source/tmanager_lib source/tests/main.cpp source/tmanager_lib/test_manager.cpp -o build/run_tests
```

Logo após a compilação, para executar os testes gerado use os comandos:

No linux:
```
./build/run_tests
```
No windows:
```
.\Debug\run_tests.exe
```
