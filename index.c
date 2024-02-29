#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct fardo{
    char cultivar[20];
    char tipoDeFeno[20];
    int diametro;
} Fardo;

typedef struct producao{
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;  
    int qtDeFardos;
    float duracao;
    struct producao *next;
    struct producao *prev;
} Producao;

typedef struct venda{
    char comprador[20];
    Fardo infosDoFeno;
    Data dataVenda;
    int qtFenoVendido;
    float preco;
    struct venda *prev;
    struct venda *next;
}Venda;


//Funções 
//função para testar se codigo já existe
int testaCodigo(Producao *first, int codigo){
    Producao *aux = first;
    while (aux != NULL) {
        if (aux->codigo == codigo) {
            printf("Nao eh possível registrar esse codigo, pois ele ja existe.\n");
            return 1; // Código já existe
        }
        aux = aux->next;
    }
    return 0; // Código não existe
}

//incluir produção
int incluirProducao(Producao **first,Producao **last, Producao *novaProducao){

     // Testa se o código já existe
    if (testaCodigo(*first, novaProducao->codigo) == 1) {
        free(novaProducao);
        return 0; // Não foi possível incluir a produção
    }

//encadeamento no final da lista
    if(*first == NULL){
        *first = novaProducao;
        *last = novaProducao;
    } else {
        (*last)->next = novaProducao;
        novaProducao->prev = *last;
        *last = novaProducao;
    }
    return 1;
}

void consultarProducaoData(Producao *first, Data *date) {
    Producao *aux = first;
    int encontrou = 0;
    
    while (aux != NULL) {
        if (aux->dataProducao.dia == date->dia && aux->dataProducao.mes == date->mes && aux->dataProducao.ano == date->ano) { //então data existe
            printf("%2d/%2d/%4d %s - %s - %d\n", date->dia, date->mes, date->ano,aux->tipoDeFardo.cultivar, aux->tipoDeFardo.tipoDeFeno, aux->qtDeFardos);
            encontrou = 1;
        }
        aux = aux->next;
    }
    if(encontrou == 0){
        printf("Data nao encontrada, por favor tente com outra opcao.");
    }
}


void consultarProducaoCultivar(Producao *first, char *cultivar) {
    Producao*aux = first;
    int encontrou = 0;
    int somaQtFardos = 0;
    while (aux != NULL) {
        if (strcmp(aux->tipoDeFardo.cultivar, cultivar) == 0) {
            somaQtFardos += aux->qtDeFardos;
            printf("%s - %s - %d\n", cultivar,aux->tipoDeFardo.tipoDeFeno, somaQtFardos);
            encontrou = 1;
        }
        aux = aux->next;
    }
    if(encontrou == 0){
        printf("Nao ha registros encontrados com essa especie de cultivo.");
    }
}


void alterarProducao(Producao *first,int codigo){
    Producao *aux = first;

    while(aux != NULL){
        if(aux->codigo == codigo){
            int opcaoCampo;

            printf("\nDigite o numero do campo que deseja alterar:\n");
            printf("1. Codigo\n");
            printf("2. Data (dia/mes/ano)\n");
            printf("3. Cultivar\n");
            printf("4. Tipo de Feno\n");
            printf("5. Diametro\n");
            printf("6. Quantidade de Fardos\n");
            printf("7. Duracao\n");
            printf("8. Voltar ao menu principal\n");

            scanf("%d", &opcaoCampo);

            if (opcaoCampo < 1 || opcaoCampo > 7){
                printf("Opção inválida.\n");
                continue;
            }

            if(opcaoCampo == 1){
                printf("Digite o novo codigo:\n");
                scanf("%d", &aux->codigo);
            } 
            else if(opcaoCampo == 2){
                printf("Digite a nova data (dia/mes/ano):\n");
                scanf("%2d/%2d/%4d", &aux->dataProducao.dia, &aux->dataProducao.mes, &aux->dataProducao.ano);
            } 
            else if(opcaoCampo == 3){
                printf("Digite a nova cultivar(especie):\n");
                scanf("%s", aux->tipoDeFardo.cultivar);
            } 
            else if(opcaoCampo == 4){
                printf("Digite o novo tipo de feno (A, B ou C):\n");
                scanf("%s", aux->tipoDeFardo.tipoDeFeno);
            } 
            else if(opcaoCampo == 5){
                printf("Digite o novo diametro:\n");
                scanf("%d", &aux->tipoDeFardo.diametro);
            } 
            else if(opcaoCampo == 6){
                printf("Digite a nova quantidade de fardos:\n");
                scanf("%d", &aux->qtDeFardos);
            }
            else if(opcaoCampo == 7){
                printf("Digite a nova duracao em horas:\n");
                scanf("%f", &aux->duracao);
            }

            if(opcaoCampo == 8){
                // volta para o menu principal
                return;
            } 

            printf("Registro alterado com sucesso.\n");

            return;
        }

        aux = aux->next;
    }

    printf("Registro com o codigo %d nao encontrado.\n", codigo);
}

void excluirProducao(Producao **first, Producao **last, int codigo){
    Producao *aux = *first;

    while(aux != NULL){
        if(aux->codigo == codigo){
            if(aux->prev != NULL){
                aux->prev->next = aux->next;
            } 
            else{
                *first = aux->next;
            }

            if(aux->next != NULL){
                aux->next->prev = aux->prev;
            } 
            else{
                *last = aux->prev;
            }

            free(aux);
            printf("Registro excluido com sucesso.\n");
            return;
        }

        aux = aux->next;
    }

    printf("Registro com o codigo %d nao encontrado.\n", codigo);
}

void listarTodos(Producao *first){
    Producao *aux = first;

    while(aux != NULL){

        printf("Codigo: %d, Data: %2d/%2d/%4d, Cultivar: %s, Tipo de Feno: %s, Quantidade: %d\n",
                aux->codigo, aux->dataProducao.dia, aux->dataProducao.mes, aux->dataProducao.ano, 
                aux->tipoDeFardo.cultivar,
                aux->tipoDeFardo.tipoDeFeno, 
                aux->qtDeFardos);

        aux = aux->next;
    }
}

void incluirVenda(Venda **primeiro, Venda **ultimo, Venda *novaVenda){
    
    if(*primeiro == NULL){
        *primeiro = novaVenda;
        *ultimo = novaVenda;
    } else {
        (*ultimo)->next = novaVenda;
        novaVenda->prev = *ultimo;
        *ultimo = novaVenda;
    }
}

void consultarVenda(Venda *primeiro, Data *dataDaVenda){
    Venda *aux = primeiro;
    int encontrou = 0;
    while (aux != NULL) {
        if (aux->dataVenda.dia == dataDaVenda->dia && aux->dataVenda.mes == dataDaVenda->mes && aux->dataVenda.ano == dataDaVenda->ano) { //entao data existe
            
            printf("Comprador:%s\n", aux->comprador);
            printf("Especie do feno, qualidade e tamanho: %s, %s, %dcm\n",aux->infosDoFeno.cultivar,aux->infosDoFeno.tipoDeFeno,aux->infosDoFeno.diametro);
            printf("Data da venda: %2d/%2d/%4d\n", dataDaVenda->dia, dataDaVenda->mes, dataDaVenda->ano);
            printf("Fenos vendidos:%d\n",aux->qtFenoVendido);
            printf("Valor total da compra:%.2f\n", aux->qtFenoVendido * aux->preco);
            encontrou = 1;
        }
        aux = aux->next;
    }
    if(encontrou == 0){
        printf("Não ha registros encontrados com essa data.");
    }
}

void consultarVendaComprador(Venda *primeiro, Venda *compradorDaVenda){
    Venda *aux = primeiro;
    int encontrou = 0;
    while (aux != NULL) {
        if (strcmp(aux->comprador, compradorDaVenda->comprador) == 0){
            printf("Comprador:%s\n", aux->comprador);
            printf("Especie do feno, qualidade e tamanho: %s, %s, %dcm\n",aux->infosDoFeno.cultivar, aux->infosDoFeno.tipoDeFeno, aux->infosDoFeno.diametro);
            printf("Data da venda: %2d/%2d/%4d\n", aux->dataVenda.dia, aux->dataVenda.mes, aux->dataVenda.ano);
            printf("Fenos vendidos:%d\n",aux->qtFenoVendido);
            printf("Valor total da compra:%.2f", aux->qtFenoVendido * aux->preco);
            encontrou =1;
        }
        aux = aux->next;
    }
    if(encontrou == 0){
        printf("Não ha registros encontrados com esse comprador.");
    }
}


void listarVendas(Venda *primeiro){
    Venda *aux = primeiro;
    while(aux != NULL){
        printf("Comprador:%s\n", aux->comprador);
        printf("Especie do feno, qualidade e tamanho: %s, %s, %dcm\n",aux->infosDoFeno.cultivar, aux->infosDoFeno.tipoDeFeno, aux->infosDoFeno.diametro);
        printf("Data da venda: %2d/%2d/%4d\n", aux->dataVenda.dia, aux->dataVenda.mes, aux->dataVenda.ano);
        printf("Fenos vendidos:%d\n",aux->qtFenoVendido);

        aux = aux->next;
    }
}

int main(){
    int opcao;
    Producao *first =NULL, *last =NULL;
    Venda *primeiro = NULL, *ultimo = NULL;

    while(1){
        printf(" Digite:\n 1- Incluir Producao\n 2- Consultar\n 3- Alterar\n 4- Excluir\n 5- Listar todos\n 6- Incluir venda\n 7- Consultar vendas\n 8- Listar Vendas\n 9- Sair\n");
        scanf("%d", &opcao);

        if(opcao == 1){
            int opcaoTipoDeFeno;
            int opcaoTipoDeCultivar;
            int opcaoDeDiametro;
            Producao *novaProducao = (Producao *)malloc(sizeof(Producao));
            if(novaProducao == NULL)return 1;
            printf("Digite o codigo da producao:\n");
            scanf("%d", &novaProducao->codigo);

            printf("Digite a data:\n");
            scanf("%2d/%2d/%4d", &novaProducao->dataProducao.dia, &novaProducao->dataProducao.mes, &novaProducao->dataProducao.ano);

            printf("Selecione a especie(cultivar):\n 1-Tifton 85\n");
            printf(" 2-Jiggs\n");
            printf(" 3-Coastcross\n");
            scanf("%d", &opcaoTipoDeCultivar);
            if(opcaoTipoDeCultivar == 1){
                strcpy(novaProducao->tipoDeFardo.cultivar, "Tifton 85");
            }
            else if(opcaoTipoDeCultivar == 2){
                strcpy(novaProducao->tipoDeFardo.cultivar, "Jiggs");
            }else if(opcaoTipoDeCultivar == 3){
                strcpy(novaProducao->tipoDeFardo.cultivar, "Coastcross");
            }else{
                printf("Opcao invalida\n");
                return 1;
            }

            printf("Digite o tipo de feno:\n1-A(Melhor qualidade, nao tomou chuva e poucos talos.)\n");
            printf("2-B(Tomou um pouco de chuva ou maior quantidade de talos.)\n");
            printf("3-C(Mais talos ou apresenta ervas daninha.)\n");
            scanf("%d", &opcaoTipoDeFeno);
            if(opcaoTipoDeFeno == 1){
                strcpy(novaProducao->tipoDeFardo.tipoDeFeno,"A");
            }else if(opcaoTipoDeFeno == 2){
                strcpy(novaProducao->tipoDeFardo.tipoDeFeno,"B");
            }else if(opcaoTipoDeFeno ==3){
                strcpy(novaProducao->tipoDeFardo.tipoDeFeno,"C");
            }else{
                printf("Opcao invalida\n");
                return 1;
            }

                printf("Selecione o diametro do feno:\n1- 80cm\n");
                printf("2- 90cm\n");
                printf("3- 100cm\n");
                printf("4- 110cm\n");
                printf("5- 120cm\n");
                printf("6- 130cm\n");
                printf("7- 140cm\n");
                printf("8- 150cm\n");
                printf("9- 160cm\n");
                scanf("%d", &opcaoDeDiametro);
                if(opcaoDeDiametro == 1){
                    novaProducao->tipoDeFardo.diametro=80;
                }else if(opcaoDeDiametro == 2){
                    novaProducao->tipoDeFardo.diametro=90;
                }else if(opcaoDeDiametro == 3){
                    novaProducao->tipoDeFardo.diametro=100;
                }else if(opcaoDeDiametro == 4){
                    novaProducao->tipoDeFardo.diametro=110;
                }else if(opcaoDeDiametro == 5){
                    novaProducao->tipoDeFardo.diametro=120;
                }else if(opcaoDeDiametro == 6){
                    novaProducao->tipoDeFardo.diametro=130;
                }else if(opcaoDeDiametro == 7){
                    novaProducao->tipoDeFardo.diametro=140;
                }else if(opcaoDeDiametro == 8){
                    novaProducao->tipoDeFardo.diametro=150;
                }else if(opcaoDeDiametro == 9){
                    novaProducao->tipoDeFardo.diametro=160;
                }else{
                    printf("Opcao invalida\n");
                    return 1;
                }

                printf("Digite a quantidade de fardos produzidos:\n");
                scanf("%d", &novaProducao->qtDeFardos);
                printf("Digite a duracao em horas:\n");
                scanf("%f", &novaProducao->duracao);
                novaProducao->next = NULL;
                novaProducao->prev = NULL;                    
                incluirProducao(&first, &last, novaProducao);
        }   

        if(opcao == 2){
            int opcConsulta;
            Data date;
            int opcCultivar = 0;
            Fardo *especieCultivo;
            especieCultivo = malloc(sizeof(Fardo));

            printf("Voce deseja consultar a producao atraves de:\n 1-Data\n 2-Cultivar\n");
            scanf("%d", &opcConsulta);
            if(opcConsulta == 1){
                printf("Digite a data que voce deseja consultar:\n");
                scanf("%2d/%2d/%4d", &date.dia, &date.mes, &date.ano);

                consultarProducaoData(first, &date);
            }else if(opcConsulta==2){
                printf("Selecione a espécie(cultivar):\n 1-Tifton 85\n");
                printf(" 2-Jiggs\n");
                printf(" 3-Coastcross\n");
                scanf("%d", &opcCultivar);
                if(opcCultivar == 1){
                    strcpy(especieCultivo->cultivar, "Tifton 85");
                    consultarProducaoCultivar(first, especieCultivo->cultivar);
                }
                else if(opcCultivar == 2){
                    strcpy(especieCultivo->cultivar, "Jiggs");
                    consultarProducaoCultivar(first, especieCultivo->cultivar);
                }else if(opcCultivar == 3){
                    strcpy(especieCultivo->cultivar, "Coastcross");
                    consultarProducaoCultivar(first, especieCultivo->cultivar);
                }else{
                    printf("Opcao invalida\n");
                    return 1;
                }
            }
        }

        if(opcao == 3){
            //alterar
            int codigoAlterar;

            printf("Digite o codigo do registro a ser alterado:\n");
            scanf("%d", &codigoAlterar);

            alterarProducao(first, codigoAlterar);
        }

        if(opcao == 4){
            //exluir
            int codigoExcluir;

            printf("Digite o codigo do registro a ser excluido:\n");
            scanf("%d", &codigoExcluir);

            excluirProducao(&first, &last, codigoExcluir);
        }

        if(opcao == 5){
            //lista todos os registros
            listarTodos(first);
        }
        
        if( opcao == 6){
            //incluir venda
            char nomeComprador[20];
            int opcaoTipoDeCultivar;
            int opcaoTipoDeFeno;
            int opcaoDeDiametro;
            Venda *novaVenda = (Venda *)malloc(sizeof(Venda));
            printf("Qual o nome do comprador:");
            scanf("%s", nomeComprador);  
            strcpy(novaVenda->comprador, nomeComprador);
            printf("Qual a especie(cultivar):\n 1-Tifton 85\n");
            printf(" 2-Jiggs\n");
            printf(" 3-Coastcross\n");
            scanf("%d", &opcaoTipoDeCultivar);
            if(opcaoTipoDeCultivar == 1){
                strcpy(novaVenda->infosDoFeno.cultivar, "Tifton 85");
            }
            else if(opcaoTipoDeCultivar == 2){
                strcpy(novaVenda->infosDoFeno.cultivar, "Jiggs");
            }else{
                strcpy(novaVenda->infosDoFeno.cultivar, "Coastcross");
            }

            printf("Digite o tipo de feno:\n1-A(Melhor qualidade, nao tomou chuva e poucos talos.)\n");
            printf("2-B(Tomou um pouco de chuva ou maior quantidade de talos.)\n");
            printf("3-C(Mais talos ou apresenta ervas daninha.)\n");
            scanf("%d", &opcaoTipoDeFeno);
            if(opcaoTipoDeFeno == 1){
                strcpy(novaVenda->infosDoFeno.tipoDeFeno,"A");
            }else if(opcaoTipoDeFeno == 2){
                strcpy(novaVenda->infosDoFeno.tipoDeFeno,"B");
            }else if(opcaoTipoDeFeno == 3){
                strcpy(novaVenda->infosDoFeno.tipoDeFeno,"C");
            }else{
                printf("Opcao invalida");
                return 1;
            }

            printf("Selecione o diametro do feno:\n1- 80cm\n");
            printf("2- 90cm\n");
            printf("3- 100cm\n");
            printf("4- 110cm\n");
            printf("5- 120cm\n");
            printf("6- 130cm\n");
            printf("7- 140cm\n");
            printf("8- 150cm\n");
            printf("9- 160cm\n");
            scanf("%d", &opcaoDeDiametro);
            if(opcaoDeDiametro == 1){
                novaVenda->infosDoFeno.diametro=80;
            }else if(opcaoDeDiametro == 2){
                novaVenda->infosDoFeno.diametro=90;
            }else if(opcaoDeDiametro == 3){
                novaVenda->infosDoFeno.diametro=100;
            }else if(opcaoDeDiametro == 4){
                novaVenda->infosDoFeno.diametro=110;
            }else if(opcaoDeDiametro == 5){
                novaVenda->infosDoFeno.diametro=120;
            }else if(opcaoDeDiametro == 6){
                novaVenda->infosDoFeno.diametro=130;
            }else if(opcaoDeDiametro == 7){
                novaVenda->infosDoFeno.diametro=140;
            }else if(opcaoDeDiametro == 8){
                novaVenda->infosDoFeno.diametro=150;
            }else if(opcaoDeDiametro == 9){
                novaVenda->infosDoFeno.diametro=160;
            }else{
                printf("Opcao invalida");
                return 1;
            }
            printf("Digite a data:\n");
            scanf("%2d/%2d/%4d", &novaVenda->dataVenda.dia, &novaVenda->dataVenda.mes, &novaVenda->dataVenda.ano);

            printf("Digite a quantidade de fardos vendidos:\n");
            scanf("%d", &novaVenda->qtFenoVendido);

            printf("Digite o valor da unidade do feno vendido:\n");
            scanf("%f", &novaVenda->preco);

            novaVenda->prev =NULL;
            novaVenda->next =NULL;
            incluirVenda(&primeiro, &ultimo, novaVenda);
        }

        if(opcao == 7){
            //consultar vendas
            int opcConsulta;

            printf("Digite a forma que voce deseja consultar a venda:\n ");
            printf("1-Data da venda.\n 2-Comprador.\n");
            scanf("%d",&opcConsulta);

            if(opcConsulta == 1){
                Data *dataVenda;
                dataVenda = malloc(sizeof(Data));
                printf("Digite a data que voce deseja consultar:\n");
                scanf("%2d/%2d/%4d", &dataVenda->dia, &dataVenda->mes, &dataVenda->ano);
                consultarVenda(primeiro, dataVenda);
            }
            if(opcConsulta == 2){
                char nomeDoComprador[20];
                Venda *nomeComprador;
                nomeComprador = malloc(sizeof(Venda));
                printf("Digite o nome do comprador:\n");
                scanf("%s", nomeDoComprador);
                strcpy(nomeComprador->comprador, nomeDoComprador);
                consultarVendaComprador(primeiro, nomeComprador);
            }
        }

        if(opcao == 8){
            //listar vendas
            listarVendas(primeiro);
        }
        if(opcao==9){
            printf("Programa Encerrado\n");
            break;
        }

    }
}