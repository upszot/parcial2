#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int flag_sinRAM=0;
    void **pTemp;
    if(this != NULL && pElement!= NULL )
    {
        if(al_len(this) == this->reservedSize)
        {
            flag_sinRAM=resizeUp(this);
        }

        if(flag_sinRAM == 0 )
        {
            //this->pElements[this->size]=pElement;
            *((this->pElements) + (this->size))=pElement;
            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(this->pElements!=NULL)
        {
            free(this->pElements);
        }
        free(this);
        returnAux = 0;
    }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;
    //if(this!=NULL && (index>=0 && index < al_len(this)))
    if(this!=NULL && (index>=0 && index < this->len(this)))
    {
        if(this->pElements != NULL)
        {
            returnAux= *(this->pElements + index);
        }
    }
    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL)
    {
        returnAux = 0;
        for(int i=0;i < al_len(this) ;i++)
        {
            //if( *(this->pElements+i) == pElement)
            if( this->get(this,i) == pElement)
            {//encontro
                returnAux = 1;
                break;
            }
        }
    }
    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL && (index>=0 && index <= al_len(this)) )
    {
        if(index==al_len(this))
        {
            returnAux=al_add(this,pElement);
        }
        else
        {
            *(this->pElements+index)=pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)
{
    int returnAux = -1;
    if(this!=NULL && (index>=0 && index < al_len(this)) )
    {
        if(contract(this,index)==0)
        {
            this->size-=1;
            resizeDown(this);
            returnAux = 0;
        }
    }
    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        this->size=0;
        resizeDown(this);
        returnAux = 0;
    }
    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
{
    ArrayList* returnAux = NULL;
    if(this!=NULL)
    {
       returnAux=al_subList(this,0,al_len(this));
    }
    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL && (index>=0 && index <= al_len(this) )  )
    {
/*        if(al_len(this)==index)
        {
             returnAux=al_add(this,pElement);
        }
        else
        {
            if(expand(this,index) == 0)
            {
                returnAux=al_set(this,index,pElement);
            }
        }
*/
        if(expand(this,index) == 0)
        {
            returnAux=al_set(this,index,pElement);
        }
    }
    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL)
    {
        for(int i=0;i < al_len(this) ;i++)
        {
            if( this->get(this,i) == pElement)
            {//encontro
                returnAux = i;
                break;
            }
        }
    }
    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if( al_len(this)==0)
        {
           returnAux=1;
        }
        else
        {
            returnAux=0;
        }
    }
    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index)
{
    void* returnAux = NULL;
    if(this!=NULL && (index>=0 && index < al_len(this)) )
    {
        returnAux=this->get(this,index);
        if(al_remove(this,index) !=0)
        {
            returnAux = NULL;
        }
    }
    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)
{
    ArrayList* returnAux = NULL;
    void* pElement;

    if(this!=NULL && from >=0 && to <= this->len(this) && from <to )
    {
        returnAux=al_newArrayList();
        for(int i=from; i<to ;i++)
        {
            pElement=al_get(this,i);
            if(pElement==NULL || returnAux->add(returnAux ,pElement) !=0 )
            {
                al_deleteArrayList(returnAux);
                returnAux = NULL;
                break;
            }
        }//FIN for(int i=from; i<to ;i++)
    }
    return returnAux ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)
{
    int returnAux = -1;
    int NoEncontro=0;

    if(this!=NULL && this2!=NULL )
    {
        returnAux = 0;
        if(this2->len(this2) <= this->len(this) )
        {//this2 tiene que estar contenido en this
            for(int i=0;i<al_len(this);i++)
            {
                if(al_contains(this , this2->get(this2,i) ) != 1)
                {
                    NoEncontro=1;
                    break;
                }
            }

            if(NoEncontro==0)
            {
                returnAux = 1;
            }
        }//FIN if(this->len(this) == this2->len(this2) )
    }//FIN if(this!=NULL && this2!=NULL )

    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;
    void* AuxElement;
    if(this !=NULL && pFunc!=NULL && (order==0 ||order==1) )
    {
        returnAux = 0;
        for(int i=0;i<al_len(this)-1;i++)
        {
            for(int j=i+1;j<al_len(this);j++)
            {
                if(order==0)
                {
                    if(pFunc(al_get(this,i),al_get(this,j)) <0)
                    {
                        AuxElement=al_get(this,i);
                        al_set(this,i,al_get(this,j));
                        al_set(this,j,AuxElement);
                    }
                }
                else
                {
                    if(pFunc(al_get(this,i),al_get(this,j)) >0)
                    {
                        AuxElement=al_get(this,j);
                        al_set(this,j,al_get(this,i));
                        al_set(this,i,AuxElement);
                    }
                }//if(order==0)
            }//for(int j=i+1;j<al_len(this)-1;j++)
        }//for(int i=0;i<al_len(this);i++)
    }
    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;

    void **pTemp;
    if(this != NULL )
    {
        if(al_len(this) == this->reservedSize)
        {
            pTemp= (void **) realloc(this->pElements,sizeof(void *) * (al_len(this) + AL_INCREMENT) );
            if(pTemp!=NULL)
            {
                returnAux = 0;
                this->pElements=pTemp;
                this->reservedSize+=AL_INCREMENT;
            }
        }
    }

    return returnAux;
}

/** \brief Decrementa the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeDown(ArrayList* this)
{
    int returnAux = -1;

    void **pTemp;
    if(this != NULL )
    {
        if(al_len(this) + AL_INCREMENT  > this->reservedSize)
        {
            pTemp= (void **) realloc(this->pElements,sizeof(void *) * (al_len(this) + AL_INCREMENT) );
            if(pTemp!=NULL)
            {
                returnAux = 0;
                this->pElements=pTemp;
                this->reservedSize=al_len(this)+AL_INCREMENT;
            }
        }
    }

    return returnAux;
}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux = -1;
    int flag_error=0;
    int len=al_len(this);
    if(this!=NULL && len !=-1 && (index>=0 && index <= len) )
    {
        for(int i=al_len(this); i>index; i--)
        {
            if(i==al_len(this))
            {//ultimo elemento
                if(al_add(this,al_get(this,i-1))!=0)
                {
                    flag_error=1;
                    break;
                }
            }
            else
            {
                if(al_set(this,i,al_get(this,i-1)) !=0)
                {
                    flag_error=1;
                    break;
                }
            }
        }//FIN for(int i=al_len(this); i<= index;i--)
        if(flag_error==0)
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;

    if(this!=NULL && (index>=0 && index < al_len(this)) )
    {
        for(int i=index; i< al_len(this);i++)
        {
            *(this->pElements+i)= *(this->pElements +i +1);
        }
        returnAux = 0;
    }
    return returnAux;
}
