//Jean Lucas, Otacilio Henrique,Marcus Vinivius

#define T = 2
#define MAX_CHAVES  2 * T - 1
#define MAX_FILHOS  2 * T
#define MIN_OCUP  T - 1

typedef struct no_arvoreB {
   int num_chaves;
   int chaves[MAX_CHAVES];
   arvoreB *filhos[MAX_FILHOS];
}arvoreB;

void insere_chave(arvoreB *raiz, int info, arvoreB *filhodir)
{
  int k, pos;
  
  pos = busca_binaria(raiz, info);
  k = raiz->num_chaves;

  while (k > pos && info < raiz->chaves[k-1])
  {
    raiz->chaves[k] = raiz->chaves[k-1];
    raiz->filhos[k+1] = raiz->filhos[k];
    k--;
  }
  
  raiz->chaves[pos] = info;
  raiz->filhos[pos+1] = filhodir;
  raiz->num_chaves++;
}


arvoreB *insere(arvoreB *raiz, int info, bool *h, int *info_retorno)
{
  int i, j, pos,
      info_mediano;
  arvoreB *temp, *filho_dir;

  if (raiz == NULL)
   {
     *h = true;
     *info_retorno = info;
     return(NULL);
   }
  else {
         pos = busca_binaria(raiz,info);
         if (raiz->num_chaves > pos && raiz->chaves[pos] == info)
           {
             printf("Chave ja contida na arvore");
             *h = false;
           }
         else {
               filho_dir = insere(raiz->filhos[pos],info,h,info_retorno);
               if (*h)
                 {
                     if (raiz->num_chaves < MAX_CHAVES)
                     {
                       insere_chave(raiz, *info_retorno, filho_dir);
                       *h = false;
                     }
                   else { //Overflow. Precisa subdividir
                          temp = (arvoreB *) malloc (sizeof(arvoreB));
                          temp->num_chaves = 0;

                        
                         for (i = 0; i < MAX_FILHOS; i++)
                           temp->filhos[i] = NULL;

                         
                         info_mediano = raiz->chaves[MIN_OCUP];

                        
                         temp->filhos[0] = raiz->filhos[MIN_OCUP+1];
                         for (i = MIN_OCUP + 1; i < MAX_CHAVES; i++)
                           insere_chave(temp, raiz->chaves[i], raiz->filhos[i+1]);

                         
                         for (i = MIN_OCUP; i<MAX_CHAVES; i++)
                         {
                           raiz->chaves[i] = 0;
                           raiz->filhos[i+1] = NULL;
                         }
                         raiz->num_chaves = MIN_OCUP;

                         
                         if (pos <= MIN_OCUP)
                              insere_chave(raiz, *info_retorno, filho_dir);
                         else insere_chave(temp, *info_retorno, filho_dir);

                         
                         *info_retorno = info_mediano;
                         return(temp);
                       }
                 }
              }
     }
}

arvoreB *insere_arvoreB(arvoreB *raiz, int info)
{
  bool h;
  int info_retorno, i;
  arvoreB *filho_dir, *nova_raiz;

  filho_dir = insere(raiz,info,&h,&info_retorno);
  if (h)
   { 
     nova_raiz = (arvoreB *) malloc (sizeof(arvoreB));
     nova_raiz->num_chaves = 1;
     nova_raiz->chaves[0] = info_retorno;
     nova_raiz->filhos[0] = raiz;
     nova_raiz->filhos[1] = filho_dir;
     for (i = 2; i <= MAX_CHAVES; i++)
       nova_raiz->filhos[i] = NULL;
     return(nova_raiz);
   }
  else return(raiz);
}
