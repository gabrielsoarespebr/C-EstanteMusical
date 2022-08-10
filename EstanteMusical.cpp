/*
IFPE
Analise e Desenvolvimento de Sistemas
Introducao a programacao
Gabriel Soares

Projeto: ESTANTE MUSICAL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ITENS 100 //Quantidade de musicas suportada pela estante
#define MAX_STRING_GRANDE 20 //Quantidade suficiente de caracteres para nome de musica e de artista/banda
#define MAX_STRING_PEQUENA 10 //Quantidade suficiente de caracteres para nome de genero musical e ano de lancamento

typedef enum{
    TELA_PRINCIPAL = 0,
    TELA_ADICIONAR = 1,
    TELA_LISTAR = 2,
    TELA_EXCLUIR = 3,
    TELA_SAIR = 4,
	} Telas;
    
typedef struct{
    char artistaBanda[MAX_STRING_GRANDE];
    char musica[MAX_STRING_GRANDE];
    char genero[MAX_STRING_PEQUENA];
    char ano[MAX_STRING_PEQUENA];
	} Musica;

typedef struct{
    Telas menu;
    int totalMusicas;
    Musica musicas[MAX_ITENS];
	} EstanteMusical;

int main(){
    EstanteMusical estante;
    memset(&estante,0x0, sizeof(estante)); //Zera todos os bytes da estante
    estante.menu = TELA_PRINCIPAL; //Menu
    
    FILE * memoria= fopen ("musicas.bin","rb");
    if (memoria == NULL)
	{
        printf("Nao foi encontrado o arquivo 'musicas.bin'. Reinstale o programa ou entre em contato com o fornecedor.");
        return 1;
    }
    
    size_t lidos = fread(estante.musicas, sizeof(Musica), MAX_ITENS, memoria);
    printf("Itens lidos: %zd.\n",lidos);
    estante.totalMusicas = (int)lidos;
    fclose(memoria);
    
    while (estante.menu != TELA_SAIR)
	{
    	switch(estante.menu)
		{
			case TELA_PRINCIPAL:
			{
				printf("\n\n-------------------------------\n");
				printf("\tESTANTE MUSICAL\n");
				printf("-------------------------------\n");
				printf("Seja bem-vindo(a) a sua Estante Musical.\n");
				int opcao = 4; //Pre-definicao que: 1) descarta o valor residual que havia no endereco de memoria; 2) chama a funcao TELA_SAIR se o usuario nao mudar o valor da vairavel
				
				do
				{
				printf("Selecione uma opcao:\n");
				printf("\t[1] Cadastro de musica.\n");
				printf("\t[2] Lista de musicas.\n");
				printf("\t[3] Excluir musica.\n");
				printf("\t[4] Sair do programa.\n");
				scanf("%d",&opcao);
				} while (opcao < 1 || opcao > 4);
				
				if (opcao == 1)
				{
					estante.menu = TELA_ADICIONAR;
					if (estante.totalMusicas >= MAX_ITENS)
					{
						printf("Estante lotada. Exclua alguma musica antes de adicionar novas musicas.\n");
						estante.menu = TELA_PRINCIPAL;
					}
				}
				
				if (opcao == 2)
				{
					estante.menu = TELA_LISTAR;
					if (estante.totalMusicas == 0)
					{
						printf("[!]\tEstante vazia. Nao ha musicas para listar.\n\n");
						estante.menu = TELA_PRINCIPAL;
					}
				}
				
				if (opcao == 3)
				{
					estante.menu = TELA_EXCLUIR;
					if (estante.totalMusicas == 0)
					{
						printf("[!]\tEstante vazia. Nao ha musicas para excluir.\n\n");
						estante.menu = TELA_PRINCIPAL;
					}
				}
				
				if (opcao == 4)
				{
					estante.menu = TELA_SAIR;
				}
				
				break;
			}
			
			case TELA_ADICIONAR:
			{
				getchar();
				printf("-------------------------------\n");
				printf("\tADICIONANDO MUSICA\n");
				printf("-------------------------------\n");
				Musica novaMusica;
				int opcao = 1;
				
				do
				{
	            	memset(&novaMusica, 0x0, sizeof(novaMusica));
	            	
					printf("Insira o nome do(a) artista/banda: ");
					fgets(novaMusica.artistaBanda, 128, stdin);
					novaMusica.artistaBanda[strcspn(novaMusica.artistaBanda, "\n")] = '\0';
					
					printf("Insira o nome da musica: ");
					fgets(novaMusica.musica, 128, stdin);
					novaMusica.artistaBanda[strcspn(novaMusica.artistaBanda, "\n")] = '\0';
					
					printf("Insira o genero: ");
					fgets(novaMusica.genero, 128, stdin);
					novaMusica.artistaBanda[strcspn(novaMusica.artistaBanda, "\n")] = '\0';
					
					printf("Insira o ano de lancamento: ");
					fgets(novaMusica.ano, 128, stdin);
					novaMusica.artistaBanda[strcspn(novaMusica.artistaBanda, "\n")] = '\0';
					
					printf("\nTecle 1 para SALVAR, se todas as informacoes fornecidas estiverem corretas.");
					printf("\nTecle 2 para descartar as informacoes e recomecar esse processo.\n");
					scanf("%d",&opcao);
				} while (opcao == 2);
				
				estante.musicas[estante.totalMusicas] = novaMusica;
				estante.totalMusicas++;
				memoria= fopen ("musicas.bin","w+b");
				if (memoria == NULL)
				{
					printf("Nao foi encontrado o arquivo 'musicas.bin'. Reinstale o programa ou entre em contato com o fornecedor.");
					return 1;
				}
				
				size_t musicasSalvas = fwrite(estante.musicas, sizeof(Musica), estante.totalMusicas, memoria);
				if (musicasSalvas != (size_t)estante.totalMusicas)
				{
					printf("[!]\tErro ao salvar musica em musicas.bin\n");
				}
        		fclose(memoria);	
				estante.menu = TELA_PRINCIPAL;
				break;
			}
			
			case TELA_LISTAR:
			{
				printf("-------------------------------\n");
				printf("\tESTANTE MUSICAL\n");
				printf("-------------------------------\n");
				printf("ARTISTA/BANDA | MUSICA\t| GENERO\t| ANO\n");
				int ordem;
				for (ordem=0 ; ordem < estante.totalMusicas; ordem++)
				{
					printf("%s\t", estante.musicas[ordem].artistaBanda);
					printf("%s\t", estante.musicas[ordem].musica);
					printf("%s\t", estante.musicas[ordem].genero);
					printf("%s\n", estante.musicas[ordem].ano);
				}
				printf("-------------------------------\n");
				printf("Total de musicas: %d\n",ordem++);
				printf("-------------------------------");
				estante.menu = TELA_PRINCIPAL;
				break;
			}
			
			case TELA_EXCLUIR:
			{
				
				printf("-------------------------------\n");
				printf("\tESTANTE MUSICAL\n");
				printf("-------------------------------\n");
				printf("ARTISTA/BANDA | MUSICA\t| GENERO\t| ANO\n");
				int ordem;
				for (ordem=0 ; ordem < estante.totalMusicas; ordem++)
				{
					printf("%s\t", estante.musicas[ordem].artistaBanda);
					printf("%s\t", estante.musicas[ordem].musica);
					printf("%s\t", estante.musicas[ordem].genero);
					printf("%s\n", estante.musicas[ordem].ano);
				}
				printf("-------------------------------\n");
				printf("Total de musicas: %d\n",ordem++);
				printf("-------------------------------");
				
				
				printf("-------------------------------\n");
				printf("\tEXCLUINDO MUSICA\n");
				printf("-------------------------------\n");
				printf("Selecione uma opcao:\n");
				printf("\t[1] Excluir apenas uma musica.\n");
				printf("\t[2] Zerar a estante.\n");
				int opcao;
				scanf("%d",&opcao);
				
				if (opcao == 2)
				{
					memset(&estante,0x0, sizeof(estante));
					fopen ("musicas.bin","rb");
				}
				else
				{
					int excluido, i;
					do
					{
						printf("Indique a posicao da musica a ser excluida (de 1 em diante): ");
						scanf("%d", &excluido);
					} while (excluido < 0 || excluido >= estante.totalMusicas);
					
					for (i = (excluido-1); i < (estante.totalMusicas-1); i++)  
        			{  
            			estante.musicas[i] = estante.musicas[i+1];
        			}  
					estante.totalMusicas--;
				}
				
				memoria= fopen ("musicas.bin","w+b");
				if (memoria == NULL)
				{
					printf("Nao foi encontrado o arquivo 'musicas.bin'. Reinstale o programa ou entre em contato com o fornecedor.");
					return 1;
				}
				
				size_t musicasSalvas = fwrite(estante.musicas, sizeof(Musica), estante.totalMusicas, memoria);
				if (musicasSalvas != (size_t)estante.totalMusicas)
				{
					printf("[!]\tErro ao salvar musica em musicas.bin\n");
				}
        		fclose(memoria);
				
				
				estante.menu = TELA_PRINCIPAL;
				break;
			}
			
			default:
			{
				estante.menu = TELA_PRINCIPAL;
				break;
			}
		}
	}
	return 0;
}
