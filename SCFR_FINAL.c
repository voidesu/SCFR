/******************************************************************************

Alunos: Amanda Correa e Giovanni Marin
Turma: C11
Data de Início: 15/06/2026

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

// -------------------------------- STRUCTS --------------------------------    

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Cliente {
    char nome[50];
    char CPF[50];
    char telefone[15];
    Data dataNascimento;
    char numeroCartao[20];
    char chavePix[30];
} Cliente;

typedef struct Vendas {
    Cliente cliente;
    int idVenda;
    float valorTotalVenda;
    int formaPagamento;
    int qtdeParcelas;
    Data dataVenda;
    char observacao[50];
} Vendas; 

typedef struct Parcela {
    int idParcela;
    int idVenda;
    int numeroDaParcela;
    float valorDaParcela;
    Data dataVencimento;
    Data dataRecebimento;
    char situacaoDaParcela; // 'A', 'R', 'V', 'C'
} Parcela;

// -------------------------------- VARIAVEIS GLOBAIS --------------------------------    
    
Cliente cliente[20];
int qtdClientes = 0;

Vendas vetorVendas[100];
int qtdVendas = 0;

Parcela vetorParcelas[1000];
int qtdParcelas = 0;
    
// -------------------------------- PROTOTIPO DAS FUNCOES --------------------------------    
    
int validarData(Data dt);
int validarTelefone(char telefone[]);
int validarEmail(char email[]);
int validarCartao(char cartao[]);
int validarCPF(char cpf[]);

void cadastrarCliente();
void exibirCliente(Cliente c);

void buscarPorNome();
void buscarPorCPF();
void buscarPorTelefone();
void menuBuscarCliente();

void buscarVendaNome();
void buscarVendaCPF();
void buscarVendaTelefone();
void buscarVendaID();

void registroVenda(); 
void consultarVendas(); 
void gerarParcelas(Vendas v); 
void exibirVenda(Vendas v); 
void exibirParcelasVenda(int idVenda); 
void identificarParcelasVencidas(); 
void quitarParcela(); 
void liquidarDivida(); 

int calcularDiasAtraso(Data vencimento, Data pagamento);
void apresentarSituacaoDiaria();
void apresentarSituacaoMensal();
void apresentarSituacaoEmpresa();
 
// -------------------------------- MAIN --------------------------------    

int main(){
    int menu = 0;

    // Clientes Fixos para Teste
    strcpy(cliente[0].nome, "Amanda Correa");
    strcpy(cliente[0].CPF, "12135016950");
    strcpy(cliente[0].telefone, "043991231517");
    cliente[0].dataNascimento.dia = 21;
    cliente[0].dataNascimento.mes = 10;
    cliente[0].dataNascimento.ano = 2007;
    strcpy(cliente[0].numeroCartao, "4532015112830366");
    strcpy(cliente[0].chavePix, "amanda@email.com");
    qtdClientes++;

    strcpy(cliente[1].nome, "Giovanni Marin");
    strcpy(cliente[1].CPF, "52998224725");
    strcpy(cliente[1].telefone, "044991521235");
    cliente[1].dataNascimento.dia = 22;
    cliente[1].dataNascimento.mes = 11;
    cliente[1].dataNascimento.ano = 2008;
    strcpy(cliente[1].numeroCartao, "4556737586899855");
    strcpy(cliente[1].chavePix, "giovanni@email.com");
    qtdClientes++;

    do {
        printf("\n=============================================================\n");
        printf("                     PAINEL DE COMPRA E VENDAS\n");
        printf("=============================================================\n");
        printf("Desenvolvido por Amanda e Giovanni\n");
        printf("-------------------------------------------------------------\n");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("-------------------------------------------------------------\n");
        printf(" 1 - Cadastrar Cliente\n");
        printf(" 2 - Registrar Venda\n");
        printf(" 3 - Consultar Clientes\n");
        printf(" 4 - Consultar Vendas\n");
        printf(" 5 - Consultar Parcelas (Quitar Proxima)\n");
        printf(" 6 - Atualizar e Identificar Parcelas Vencidas\n");
        printf(" 7 - Liquidar Divida Total de uma Venda\n");
        printf(" 8 - Situacao Financeira Diaria\n");
        printf(" 9 - Situacao Financeira Mensal\n");
        printf("10 - Situacao Financeira Geral da Empresa\n");
        printf(" 0 - Sair\n");
        printf("-------------------------------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &menu);
        getchar();
        
        switch(menu) {
            case 1:
                if (qtdClientes < 20) {
                    cadastrarCliente();
                } else {
                    printf("\nLimite de clientes atingido!\n");
                }
                break;
            case 2:
                registroVenda();
                break;
            case 3:
                menuBuscarCliente();
                break;
            case 4:
                consultarVendas();
                break;
            case 5:
                quitarParcela();
                break;
            case 6:
                identificarParcelasVencidas();
                break;
            case 7:
                liquidarDivida();
                break;
            case 8:
                apresentarSituacaoDiaria();
                break;
            case 9:
                apresentarSituacaoMensal();
                break;
            case 10:
                apresentarSituacaoEmpresa();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao Invalida!\n");
                break;
        }
    } while (menu != 0);

    return 0;
}

// -------------------------------- FUNÇÕES DE VALIDAÇÃO --------------------------------    

int validarData(Data dt) {
    int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((dt.ano % 4 == 0 && dt.ano % 100 != 0) || (dt.ano % 400 == 0)){
        diasMes[2] = 29;
    }
    if (dt.mes >= 1 && dt.mes <= 12) {
        if (dt.dia >= 1 && dt.dia <= diasMes[dt.mes]) {
            if (dt.ano >= 1900) {
                return 1;
            }
        }
    }
    return 0;
}

int validarTelefone(char telefone[]){
    int tamanho = strlen(telefone);
    int i;
    if (telefone[0] == '0') {
        if (tamanho == 11 || tamanho == 12) {
            for(i = 0; i < tamanho; i++){
                if(telefone[i] < '0' || telefone[i] > '9'){
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}

int validarEmail(char email[]) {
    int arroba = 0, posArroba = -1, posPonto = -1, i;
    for (i = 0; i < strlen(email); i++) {
        if(email[i] == '@') {
            arroba++;
            posArroba = i;
        }
        if (email[i] == '.') {
            posPonto = i;
        }
    }
    if (arroba != 1) return 0;
    if (posArroba < 2) return 0;
    if (posPonto == -1) return 0;
    if (posPonto - posArroba - 1 < 2) return 0;
    if (strlen(email) - posPonto - 1 < 2) return 0;
    return 1;
}

int validarCartao(char cartao[]){
    int tamanho = strlen(cartao);
    int numero = 0, somaLocal = 0, dobrar = 0, i;
    for(i = tamanho - 1; i >= 0; i--){
        numero = cartao[i] - '0';
        if (dobrar == 1) { 
            numero = numero * 2;
            if (numero > 9) numero = numero - 9;
        }
        somaLocal = somaLocal + numero;
        dobrar = !dobrar;
    }
    return (somaLocal % 10 == 0);
}

int validarCPF(char cpf[]) {
    char cpfLimpo[12]; 
    int k, indiceLimpo = 0;
    int somaLocal = 0, resto = 0;
    int primeiroDigito = 0, segundoDigito = 0;

    for (k = 0; cpf[k] != '\0'; k++) {
        if (cpf[k] >= '0' && cpf[k] <= '9') {
            if (indiceLimpo < 11) { 
                cpfLimpo[indiceLimpo] = cpf[k];
                indiceLimpo++;
            } else {
                return 0; 
            }
        }
    }
    cpfLimpo[indiceLimpo] = '\0'; 

    if (indiceLimpo != 11) return 0;

    somaLocal = 0;
    int peso = 10;
    for (k = 0; k < 9; k++) {
        somaLocal += (cpfLimpo[k] - '0') * peso;
        peso--;
    }
    resto = (somaLocal * 10) % 11;
    primeiroDigito = (resto == 10 || resto == 11) ? 0 : resto;

    somaLocal = 0;
    peso = 11;
    for (k = 0; k < 10; k++) {
        somaLocal += (cpfLimpo[k] - '0') * peso;
        peso--;
    }
    resto = (somaLocal * 10) % 11;
    segundoDigito = (resto == 10 || resto == 11) ? 0 : resto;

    return (cpfLimpo[9] - '0' == primeiroDigito && cpfLimpo[10] - '0' == segundoDigito);
}

// -------------------------------- FUNÇÕES DE CLIENTE --------------------------------    

void cadastrarCliente() {
    printf("\nNome..: ");
    fgets(cliente[qtdClientes].nome, 50, stdin);
    cliente[qtdClientes].nome[strcspn(cliente[qtdClientes].nome, "\n")] = '\0';

    printf("CPF..: ");
    fgets(cliente[qtdClientes].CPF, 50, stdin);
    cliente[qtdClientes].CPF[strcspn(cliente[qtdClientes].CPF, "\n")] = '\0';
    while (validarCPF(cliente[qtdClientes].CPF) == 0) {
        printf("CPF INVALIDO! Tente novamente..: ");
        fgets(cliente[qtdClientes].CPF, 50, stdin);
        cliente[qtdClientes].CPF[strcspn(cliente[qtdClientes].CPF, "\n")] = '\0';
    }

    printf("Telefone..: ");
    fgets(cliente[qtdClientes].telefone, 15, stdin);
    cliente[qtdClientes].telefone[strcspn(cliente[qtdClientes].telefone, "\n")] = '\0';
    while (validarTelefone(cliente[qtdClientes].telefone) == 0) {
        printf("TELEFONE INVALIDO! Tente novamente..: ");
        fgets(cliente[qtdClientes].telefone, 15, stdin);
        cliente[qtdClientes].telefone[strcspn(cliente[qtdClientes].telefone, "\n")] = '\0';
    }

    printf("Data de Nascimento (dd/mm/aaaa)..: ");
    scanf("%d/%d/%d", &cliente[qtdClientes].dataNascimento.dia, &cliente[qtdClientes].dataNascimento.mes, &cliente[qtdClientes].dataNascimento.ano);
    getchar();
    while (validarData(cliente[qtdClientes].dataNascimento) == 0) {
        printf("DATA INVALIDA! Tente novamente..: ");
        scanf("%d/%d/%d", &cliente[qtdClientes].dataNascimento.dia, &cliente[qtdClientes].dataNascimento.mes, &cliente[qtdClientes].dataNascimento.ano);
        getchar();
    }

    printf("Numero do Cartao...: ");
    fgets(cliente[qtdClientes].numeroCartao, 20, stdin);
    cliente[qtdClientes].numeroCartao[strcspn(cliente[qtdClientes].numeroCartao, "\n")] = '\0';
    while (validarCartao(cliente[qtdClientes].numeroCartao) == 0) {
        printf("NUMERO DO CARTAO INVALIDO! Tente novamente..: ");
        fgets(cliente[qtdClientes].numeroCartao, 20, stdin);
        cliente[qtdClientes].numeroCartao[strcspn(cliente[qtdClientes].numeroCartao, "\n")] = '\0';
    }

    printf("Chave Pix...: ");
    fgets(cliente[qtdClientes].chavePix, 30, stdin);
    cliente[qtdClientes].chavePix[strcspn(cliente[qtdClientes].chavePix, "\n")] = '\0';
    while (validarEmail(cliente[qtdClientes].chavePix) == 0){
        printf("CHAVE PIX INVALIDA! Tente novamente..: ");
        fgets(cliente[qtdClientes].chavePix, 30, stdin);
        cliente[qtdClientes].chavePix[strcspn(cliente[qtdClientes].chavePix, "\n")] = '\0';
    }
    
    qtdClientes++; 
    printf("\n Cadastro Completo!!\n");
}

void exibirCliente(Cliente c) {
    printf("\nNome: %s", c.nome);
    printf("\nCPF: %s", c.CPF);
    printf("\nTelefone: %s", c.telefone);
    printf("\nData de Nascimento: %02d/%02d/%04d", c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano);
    printf("\nCartao: %s", c.numeroCartao);
    printf("\nChave Pix: %s\n", c.chavePix);
}

void buscarPorNome() {
    int i;
    char nome[50];
    printf("Digite o nome..: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].nome, nome) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    printf("\nCliente nao encontrado!\n");
}

void buscarPorCPF() {
    int i;
    char CPF[50];
    printf("Digite o CPF..: ");
    fgets(CPF, 50, stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].CPF, CPF) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    printf("\nCliente nao encontrado!\n");
}

void buscarPorTelefone() {
    int i;
    char telefone[15];
    printf("Digite o telefone..: ");
    fgets(telefone, 15, stdin);
    telefone[strcspn(telefone, "\n")] = '\0'; 
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].telefone, telefone) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    printf("\nCliente nao encontrado!\n");
}

void menuBuscarCliente() {
    int menu = 0;
    printf("=============================================================\n");
    printf("                        BUSCA DE CLIENTES\n");
    printf("=============================================================\n");
    printf("Escolha uma das opcoes abaixo:\n");
    printf("-------------------------------------------------------------\n");
    printf("1 - Buscar cliente por Nome\n");
    printf("2 - Buscar cliente por CPF\n");
    printf("3 - Buscar cliente por Telefone\n");
    printf("-------------------------------------------------------------\n");
    printf("Opcao: ");
    scanf("%d",&menu);
    getchar();
    
    switch(menu) {
        case 1: buscarPorNome(); break;
        case 2: buscarPorCPF(); break;
        case 3: buscarPorTelefone(); break;
        default: printf("Opcao Invalida!\n");
    }
}

// -------------------------------- FUNÇÕES DE BUSCA DE VENDAS --------------------------------    

void buscarVendaNome() {
    char nome[50];
    int i, quantidade = 0;
    printf("Nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome,"\n")] = '\0';
    
    for(i = 0; i < qtdVendas; i++){
        if(strcmp(vetorVendas[i].cliente.nome, nome) == 0) {
            exibirVenda(vetorVendas[i]);
            quantidade++;
        }
    }
    if (quantidade == 0) printf("\n Nenhuma venda encontrada!");
}

void buscarVendaCPF() {
    char CPF[50];
    int i, quantidade = 0;
    printf("CPF: ");
    fgets(CPF, 50, stdin);
    CPF[strcspn(CPF,"\n")] = '\0';
    
    for(i = 0; i < qtdVendas; i++){
        if(strcmp(vetorVendas[i].cliente.CPF, CPF) == 0) {
            exibirVenda(vetorVendas[i]);
            quantidade++;
        }
    }
    if (quantidade == 0) printf("\n Nenhuma venda encontrada!");
}

void buscarVendaTelefone() {
    char telefone[15];
    int i, quantidade = 0;
    printf("Telefone: ");
    fgets(telefone, 15, stdin);
    telefone[strcspn(telefone,"\n")] = '\0';

    for(i = 0; i < qtdVendas; i++){
        if(strcmp(vetorVendas[i].cliente.telefone, telefone) == 0){
            exibirVenda(vetorVendas[i]);
            quantidade++;
        }
    }
    if(quantidade == 0) printf("\n Nenhuma venda encontrada!");
}

void buscarVendaID() {
    int id, i;
    printf("Digite o ID da venda: ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < qtdVendas; i++) {
        if (vetorVendas[i].idVenda == id) {
            exibirVenda(vetorVendas[i]);
            return;
        }
    }
    printf("\n Venda nao encontrada!");
}


int calcularDiasAtraso(Data vencimento, Data pagamento) {
    long diasVenc = vencimento.ano * 365 + vencimento.mes * 30 + vencimento.dia;
    long diasPag = pagamento.ano * 365 + pagamento.mes * 30 + pagamento.dia;
    if (diasPag > diasVenc) {
        return (int)(diasPag - diasVenc);
    }
    return 0;
}


void gerarParcelas(Vendas v){
    float valor;
    int i;
    int limite = v.qtdeParcelas;

    if(limite > 12 || limite < 1) limite = v.formaPagamento == 4 ? 12 : 1;

    for(i = 1; i <= limite; i++){
        Parcela p;
        p.idParcela = qtdParcelas + 1001;
        p.idVenda = v.idVenda;
        p.numeroDaParcela = i;

        valor = v.valorTotalVenda / limite;
        valor = valor * 1.02 * pow(1.01, i); 
        p.valorDaParcela = valor;

        p.dataVencimento = v.dataVenda;
        p.dataVencimento.mes += i;
        while(p.dataVencimento.mes > 12) {
            p.dataVencimento.mes -= 12;
            p.dataVencimento.ano++;
        }

        p.dataRecebimento.dia = 0;
        p.dataRecebimento.mes = 0;
        p.dataRecebimento.ano = 0;
        p.situacaoDaParcela = 'A';

        vetorParcelas[qtdParcelas] = p;
        qtdParcelas++;
    }
}

void registroVenda() {
    int idCliente, formaPgto, i;
    if (qtdClientes == 0) {
        printf("\nERRO -> NAO EXISTE NENHUM CLIENTE\n");
        return;
    }

    printf("\n--- CLIENTES CADASTRADOS ---\n");
    for (i = 0; i < qtdClientes; i++) {
        printf("%d - %s (CPF: %s)\n", i, cliente[i].nome, cliente[i].CPF);
    }

    printf("\nEscolha o cliente (indice): ");
    scanf("%d", &idCliente);
    getchar();

    if (idCliente < 0 || idCliente >= qtdClientes) {
        printf("\nCliente invalido!\n");
        return;
    }

    Vendas v;
    v.idVenda = qtdVendas + 1;
    v.cliente = cliente[idCliente];

    printf("Valor total da venda: R$ ");
    scanf("%f", &v.valorTotalVenda);
    getchar();

    printf("Forma de Pagamento:\n");
    printf("1 - Dinheiro\n2 - Pix\n3 - Cartao a Vista\n4 - Cartao Parcelado\n");
    printf("Opcao: ");
    scanf("%d", &formaPgto);
    getchar();

    v.formaPagamento = formaPgto;

    printf("Data da Venda (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &v.dataVenda.dia, &v.dataVenda.mes, &v.dataVenda.ano);
    getchar();

    printf("Observacao: ");
    fgets(v.observacao, 50, stdin);
    v.observacao[strcspn(v.observacao, "\n")] = '\0';

    if (formaPgto == 4) {
        do {
            printf("Quantidade de parcelas (1 a 12): ");
            scanf("%d", &v.qtdeParcelas);
            getchar();
        } while (v.qtdeParcelas < 1 || v.qtdeParcelas > 12);

        vetorVendas[qtdVendas] = v;
        gerarParcelas(v);
    } else {
        v.qtdeParcelas = 1;
        Parcela p;
        p.idParcela = qtdParcelas + 1001;
        p.idVenda = v.idVenda;
        p.numeroDaParcela = 1;
        p.valorDaParcela = v.valorTotalVenda * 1.02;

        p.dataVencimento = v.dataVenda;
        p.dataRecebimento = v.dataVenda; 
        p.situacaoDaParcela = 'R';       

        vetorVendas[qtdVendas] = v;
        vetorParcelas[qtdParcelas] = p;
        qtdParcelas++;
    }

    qtdVendas++;
    printf("\nVenda registrada com sucesso! ID da venda: %d\n", v.idVenda);
}

void consultarVendas() { 
    int opcao;
    printf("\n==================================\n");
    printf("         CONSULTAR VENDAS\n");
    printf("==================================\n");
    printf("1 - Buscar por ID da venda\n");
    printf("2 - Buscar por Nome do cliente\n");
    printf("3 - Buscar por CPF do cliente\n");
    printf("4 - Buscar por Telefone do cliente\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    getchar();
    
    switch(opcao){
        case 1: buscarVendaID(); break;
        case 2: buscarVendaNome(); break;
        case 3: buscarVendaCPF(); break;
        case 4: buscarVendaTelefone(); break;
        default: printf("OPCAO INVALIDA!!\n");
    }
}

void exibirVenda(Vendas v){
    printf("\n==============================");
    printf("\nID da venda: %d", v.idVenda);
    printf("\nCliente: %s", v.cliente.nome);
    printf("\nCPF: %s", v.cliente.CPF);
    printf("\nValor: R$ %.2f", v.valorTotalVenda);
    printf("\nForma de pagamento: ");
    switch (v.formaPagamento) {
        case 1: printf("Dinheiro"); break;
        case 2: printf("Pix"); break;
        case 3: printf("Cartao a Vista"); break;
        case 4: printf("Cartao Parcelado"); break;
    }
    printf("\nParcelas: %d", v.qtdeParcelas);
    printf("\nData: %02d/%02d/%04d", v.dataVenda.dia, v.dataVenda.mes, v.dataVenda.ano);
    printf("\nObservacao: %s\n", v.observacao);
    
    exibirParcelasVenda(v.idVenda);
}

void exibirParcelasVenda(int idVenda){
    int i;
    printf("\n------------------------------");
    printf("\n         Parcelas\n");
    printf("------------------------------");
    for(i=0; i<qtdParcelas; i++){
        if(vetorParcelas[i].idVenda == idVenda){
            printf("\nParcela %d", vetorParcelas[i].numeroDaParcela);
            printf("\nValor: R$ %.2f", vetorParcelas[i].valorDaParcela);
            printf("\nVencimento: %02d/%02d/%04d",vetorParcelas[i].dataVencimento.dia, vetorParcelas[i].dataVencimento.mes, vetorParcelas[i].dataVencimento.ano);
            printf("\nSituacao: %c\n", vetorParcelas[i].situacaoDaParcela);
        }
    }
}

void identificarParcelasVencidas (){
    int i;
    Data hoje;
    printf("Digite a data de hoje (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &hoje.dia, &hoje.mes, &hoje.ano);
    getchar();
    
    for(i=0; i < qtdParcelas; i++) {
        if(vetorParcelas[i].situacaoDaParcela == 'A') {
            if(vetorParcelas[i].dataVencimento.ano < hoje.ano) {
                vetorParcelas[i].situacaoDaParcela = 'V';
            } else if(vetorParcelas[i].dataVencimento.ano == hoje.ano && vetorParcelas[i].dataVencimento.mes < hoje.mes) {
                vetorParcelas[i].situacaoDaParcela = 'V';
            } else if(vetorParcelas[i].dataVencimento.ano == hoje.ano && vetorParcelas[i].dataVencimento.mes == hoje.mes && vetorParcelas[i].dataVencimento.dia < hoje.dia) {
                vetorParcelas[i].situacaoDaParcela = 'V';
            }
         }
    }
    printf("\n Parcelas vencidas atualizadas com sucesso!\n");
}    

void quitarParcela() {
    int idVenda, i;
    Data hoje;
    
    printf("\n==============================");
    printf("\n       Quitar Proxima Parcela\n");
    printf("------------------------------");
    printf("\nDigite o ID da venda: ");
    scanf("%d", &idVenda);
    getchar();
    
    int indice = -1;
    for (i = 0; i < qtdParcelas; i++){
        if (vetorParcelas[i].idVenda == idVenda && (vetorParcelas[i].situacaoDaParcela == 'A' || vetorParcelas[i].situacaoDaParcela == 'V')) {
            if (indice == -1 || vetorParcelas[i].numeroDaParcela < vetorParcelas[indice].numeroDaParcela) {
                indice = i;
            }
        }
    }

    if (indice != -1) {
        i = indice;
            printf("Data do pagamento hoje (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &hoje.dia, &hoje.mes, &hoje.ano);
            getchar();
            
            float valorFinal = vetorParcelas[i].valorDaParcela;
            if (vetorParcelas[i].situacaoDaParcela == 'V') {
                int dias = calcularDiasAtraso(vetorParcelas[i].dataVencimento, hoje);
                if (dias > 0) {
                    valorFinal = vetorParcelas[i].valorDaParcela * 1.02 * pow(1.0008, dias); 
                    printf("\n[ATENCAO] Parcela em atraso (%d dias). Valor original: R$ %.2f -> Corrigido: R$ %.2f", dias, vetorParcelas[i].valorDaParcela, valorFinal);
                }
            }
            
            vetorParcelas[i].valorDaParcela = valorFinal;
            vetorParcelas[i].dataRecebimento = hoje;
            vetorParcelas[i].situacaoDaParcela = 'R'; 
            
            printf("\n Parcela %d paga com sucesso! Valor Recebido: R$ %.2f\n", vetorParcelas[i].numeroDaParcela, valorFinal);
            return;
    }
    printf("\nNenhuma parcela pendente encontrada para esta venda.\n");
}

void liquidarDivida() {
    int idVenda, i, quantidade = 0;
    Data hoje;
    
    printf("\n==============================");
    printf("\n       Liquidar Dividas Totais\n");
    printf("------------------------------");
    printf("\nDigite o ID da venda: ");
    scanf("%d", &idVenda);
    getchar();
    printf("Data do pagamento (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &hoje.dia, &hoje.mes, &hoje.ano);
    getchar();
    
    for (i = 0; i < qtdParcelas; i++) {
        if(vetorParcelas[i].idVenda == idVenda && (vetorParcelas[i].situacaoDaParcela == 'A' || vetorParcelas[i].situacaoDaParcela == 'V')) {
            float valorFinal = vetorParcelas[i].valorDaParcela;
            if (vetorParcelas[i].situacaoDaParcela == 'V') {
                int dias = calcularDiasAtraso(vetorParcelas[i].dataVencimento, hoje);
                if (dias > 0) {
                    valorFinal = vetorParcelas[i].valorDaParcela * 1.02 * pow(1.0008, dias);
                }
            }
            vetorParcelas[i].valorDaParcela = valorFinal;
            vetorParcelas[i].dataRecebimento = hoje;
            vetorParcelas[i].situacaoDaParcela = 'R'; 
            printf("-> Parcela %d quitada por R$ %.2f\n", vetorParcelas[i].numeroDaParcela, valorFinal);
            quantidade++;
        }
    }
    
    if (quantidade == 0) {
        printf("\n Nenhuma Parcela pendente encontrada para liquidar.\n");
    } else {
        printf("\n Divida totalmente liquidada com sucesso! \n");
    }
}


void apresentarSituacaoDiaria() {
    Data diaFiltro;
    int i;
    float vendasRealizadas = 0, valoresRecebidos = 0, valoresAReceber = 0, valoresPendentes = 0;

    printf("\nDigite o dia de analise (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &diaFiltro.dia, &diaFiltro.mes, &diaFiltro.ano);
    getchar();

    for(i = 0; i < qtdVendas; i++) {
        if(vetorVendas[i].dataVenda.dia == diaFiltro.dia && vetorVendas[i].dataVenda.mes == diaFiltro.mes && vetorVendas[i].dataVenda.ano == diaFiltro.ano) {
            vendasRealizadas += vetorVendas[i].valorTotalVenda;
        }
    }

    for(i = 0; i < qtdParcelas; i++) {
        if(vetorParcelas[i].situacaoDaParcela == 'R' && vetorParcelas[i].dataRecebimento.dia == diaFiltro.dia && vetorParcelas[i].dataRecebimento.mes == diaFiltro.mes && vetorParcelas[i].dataRecebimento.ano == diaFiltro.ano) {
            valoresRecebidos += vetorParcelas[i].valorDaParcela;
        }
        if(vetorParcelas[i].dataVencimento.dia == diaFiltro.dia && vetorParcelas[i].dataVencimento.mes == diaFiltro.mes && vetorParcelas[i].dataVencimento.ano == diaFiltro.ano) {
            if(vetorParcelas[i].situacaoDaParcela == 'A') valoresAReceber += vetorParcelas[i].valorDaParcela;
            if(vetorParcelas[i].situacaoDaParcela == 'V') valoresPendentes += vetorParcelas[i].valorDaParcela;
        }
    }

    printf("\n=============================================");
    printf("\n  RELATORIO FINANCEIRO DIARIO: %02d/%02d/%04d", diaFiltro.dia, diaFiltro.mes, diaFiltro.ano);
    printf("\n=============================================");
    printf("\n(+) Vendas Realizadas no Dia: R$ %.2f", vendasRealizadas);
    printf("\n(+) Valores Efetivamente Recebidos: R$ %.2f", valoresRecebidos);
    printf("\n( ) Valores a Receber (Em Aberto): R$ %.2f", valoresAReceber);
    printf("\n(!) Valores Pendentes (Atrasados): R$ %.2f", valoresPendentes);
    printf("\n=============================================\n");
}

void apresentarSituacaoMensal() {
    int mes, ano, i;
    float vendasRealizadas = 0, valoresRecebidos = 0, valoresAReceber = 0, valoresPendentes = 0;

    printf("\nDigite o Mes e o Ano de analise (mm/aaaa): ");
    scanf("%d/%d", &mes, &ano);
    getchar();

    for(i = 0; i < qtdVendas; i++) {
        if(vetorVendas[i].dataVenda.mes == mes && vetorVendas[i].dataVenda.ano == ano) {
            vendasRealizadas += vetorVendas[i].valorTotalVenda;
        }
    }

    for(i = 0; i < qtdParcelas; i++) {
        if(vetorParcelas[i].situacaoDaParcela == 'R' && vetorParcelas[i].dataRecebimento.mes == mes && vetorParcelas[i].dataRecebimento.ano == ano) {
            valoresRecebidos += vetorParcelas[i].valorDaParcela;
        }
        if(vetorParcelas[i].dataVencimento.mes == mes && vetorParcelas[i].dataVencimento.ano == ano) {
            if(vetorParcelas[i].situacaoDaParcela == 'A') valoresAReceber += vetorParcelas[i].valorDaParcela;
            if(vetorParcelas[i].situacaoDaParcela == 'V') valoresPendentes += vetorParcelas[i].valorDaParcela;
        }
    }

    printf("\n=============================================");
    printf("\n  RELATORIO FINANCEIRO MENSAL: %02d/%04d", mes, ano);
    printf("\n=============================================");
    printf("\n(+) Vendas Totais do Mes: R$ %.2f", vendasRealizadas);
    printf("\n(+) Valores Recebidos no Mes: R$ %.2f", valoresRecebidos);
    printf("\n( ) Valores Vincendos (A receber): R$ %.2f", valoresAReceber);
    printf("\n(!) Valores Vencidos (Inadimplencia): R$ %.2f", valoresPendentes);
    printf("\n=============================================\n");
}

void apresentarSituacaoEmpresa() {
    int i;
    float faturamentoTotal = 0, totalRecebido = 0, totalAReceber = 0, totalVencido = 0;

    for(i = 0; i < qtdVendas; i++) {
        faturamentoTotal += vetorVendas[i].valorTotalVenda;
    }

    for(i = 0; i < qtdParcelas; i++) {
        if(vetorParcelas[i].situacaoDaParcela == 'R') totalRecebido += vetorParcelas[i].valorDaParcela;
        if(vetorParcelas[i].situacaoDaParcela == 'A') totalAReceber += vetorParcelas[i].valorDaParcela;
        if(vetorParcelas[i].situacaoDaParcela == 'V') totalVencido += vetorParcelas[i].valorDaParcela;
    }

    printf("\n=======================================================");
    printf("\n          DASHBOARD DE INDICADORES DA EMPRESA          ");
    printf("\n=======================================================");
    printf("\n[*] Faturamento Bruto Historico:  R$ %.2f", faturamentoTotal);
    printf("\n-------------------------------------------------------");
    printf("\n[+] Total em Caixa (Recebido):    R$ %.2f", totalRecebido);
    printf("\n[-] Total a Receber (Em Aberto):  R$ %.2f", totalAReceber);
    printf("\n[!] Total em Atraso (Vencido):    R$ %.2f", totalVencido);
    printf("\n=======================================================\n");
}