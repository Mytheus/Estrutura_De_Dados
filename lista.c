#include <stdio.h>

typedef struct
{
    int lista[256];
    int size;
} Lista;

int comprimento(Lista list){
    return list.size;
}
Lista removeElemento(Lista list, int elemento){
    for(int i = 0; i< list.size; i++){
        while (list.lista[i]==elemento){
            //printf("%d\n", list.lista[i]);
            if(i==list.size){
                return list;
            }
            for (int u = i; u < list.size-1;u++){
                list.lista[u] = list.lista[u+1];
            }
            list.size--;
        }
    }
    return list;
}
Lista removeElementoNoIndex(Lista list, int index){
    for (int u = index; u < list.size-1;u++){
                list.lista[u] = list.lista[u+1];
    }
    list.size--;
    return list;
}
Lista Linverte(Lista list, int aux){
    if (aux>list.size/2){
        return list;
    }
    else{
        int temp;
        temp = list.lista[aux];
        list.lista[aux] = list.lista[list.size-(aux+1)];
        list.lista[list.size-(aux+1)] = temp;
        return Linverte(list, aux+1);
    }
}
Lista inverte(Lista list){
    return Linverte(list, 0);
}

Lista insereFim(Lista list, int element){
    list.lista[list.size] = element;
    list.size++;
    return list;
}
Lista insereInicio(Lista list, int element){
    list.size++;
    for (int u = list.size-1; u >0 ; u--){
        list.lista[u] = list.lista[u-1];
    }
    //printf("problema no for");
    list.lista[0] = element;
    return list;
}

int membro(int elemento, Lista list){
    for (int i  = 0; i < list.size; i++){
        if (elemento == list.lista[i])
        {
            return 1;
        }
    }
    return 0;
}

int cabeca(Lista list){
    return list.lista[0];
}

Lista cauda(Lista list){
    Lista cauda;
    cauda.size = list.size-1;
    for (int i = 1; i < list.size; i++){
        cauda.lista[i-1] = list.lista[i];
    }
    return cauda;
}

int temDuplicadoLower(Lista list, Lista aparecidos){
    if (list.size == 0){
        return 0;
    }
    else{
        Lista aux = cauda(list);
        if (membro(cabeca(list), aux)){
            if (!membro(cabeca(list), aparecidos)){
                printf("%d\n", cabeca(list));
                aparecidos = insereInicio(aparecidos, cabeca(list));
                return temDuplicadoLower(aux, aparecidos) + 1;
            }
            else{
                return temDuplicadoLower(aux, aparecidos);
            }
        }
        else{
            return temDuplicadoLower(aux, aparecidos);
        }
    }
    
}
int temDuplicado(Lista list){
    Lista aux;
    return temDuplicadoLower(list, aux);
}

Lista concatenacao(Lista list1, Lista list2){
    int index = 0;
    for (int i = list1.size; i < list1.size+list2.size; i++){
        list1.lista[i] = list2.lista[index];
        index++;
    }
    list1.size=list1.size + list2.size;
    return list1;
}

Lista removeDuplicatas(Lista list){
    for (int i = 0; i < list.size-1; i++){
        for (int u = i+1; u < list.size; u++){
            if (list.lista[i] == list.lista[u]){
                list = removeElementoNoIndex(list, u);
            }
        }
    }
    return list;
};

int main(){
    Lista lista, lista2;
    lista.size = 0;
    lista2.size = 0; 
    printf("Quantos itens você quer inserir na lista?\n");
    scanf("%d", &lista.size);
    for (int i = 0; i < lista.size; i++)
    {
        printf("Valor na posição lista[%d]: ", i);
        scanf("%d", &lista.lista[i]);
    }
    /*if(temDuplicado(lista, size)){
        printf("Tem duplicado\n");
    }
    else
    {
        printf("Não tem duplicado\n");
    }*/
    printf("\n");
    
    lista = removeDuplicatas(lista);
    //printf("%d\n", lista.size);
    
    for (int o = 0; o < lista.size; o++)
    {
        printf("Valor na posição lista[%d]: %d\n", o, lista.lista[o]);
    }
    printf("\n");
    /*Lista aux = cauda(lista);
    for (int o = 0; o < aux.size; o++)
    {
        printf("Valor na posição lista[%d]: %d\n", o, aux.lista[o]);
    }*/
    //printf("%d", temDuplicado(lista));

}