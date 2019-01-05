#include<stdio.h>
#include<string.h>
typedef struct
{
char title[60];
char author[50];
char publisher[50];
float price;
}BOOK;
int main()
{
    BOOK book={" "," "," ",0.00};
    FILE *pFile;
    char choice,search_title[60],title[60],author[50],search_author[50];
    int n_of_records=0,i=0,k=0;
    float book_price=0;
    pFile=fopen("book.dat","ab+");
    if(pFile==NULL)
    {
        return 0;
    }
    fseek(pFile, 0, SEEK_END);
    n_of_records= ftell(pFile)/sizeof(BOOK);
    rewind(pFile);
    if(n_of_records>0 && n_of_records<40)
    {
    printf("book.dat contains %d records\n",n_of_records);
    }
    else if(n_of_records==40)
    {
        printf("The file is full");
        goto inquiry_state;
    }
    printf("Enter the name of the book\n");
    printf("To stop entering, press enter at the beginning of a line ");
    //while(strlen(fgets(book.title,60,stdin))!=1)
      entry:
          {
if (book.title== ' ')
//        if(strlen(fgets(book.title,60,stdin))==1)
        {
            goto inquiry_state;
        }
        printf("Enter the author ");
        fgets(book.author,50,stdin);
        printf("Enter the publisher ");
        fgets(book.publisher,50,stdin);
        printf("Enter the price ");
        scanf("%f",&book.price);
        fflush(stdin);
        fwrite(&book,sizeof(BOOK),1,pFile);
        n_of_records++;
        if(n_of_records==40)
        {
            goto inquiry_state;
        }
        printf("Enter the name of the book\n");
        printf("To stop entering, press enter at the beginning of a line ");
          }
          goto entry;
          inquiry_state:
              printf("Enter Q to end, or T or A to search for title and author\n");
              scanf("%c",&choice);
              switch(choice)
              {
              case 'Q':
                {
                    fclose(pFile);
                    return 0;
                }
              case 'T':
                {
                    printf("Enter the book title");
                    fflush(stdin);
                    fgets(title,60,stdin);
                    while(!feof(pFile))
                    {
                        fseek(pFile,i*sizeof(BOOK),SEEK_SET);
                        fread(&search_title,sizeof(BOOK),1,pFile);
                        if(strcmp(search_title,title)==0)
                        {
                        printf("Title %s\n",search_title);
                        fseek(pFile,(i*sizeof(BOOK))+60,SEEK_SET);
                        fread(&search_title,sizeof(BOOK),1,pFile);
                        printf("Author %s\n",search_title);
                        fseek(pFile,(i*sizeof(BOOK))+160,SEEK_SET);
                        fread(&book_price,sizeof(BOOK),1,pFile);
                        printf("Price %.2f\n",book_price);
                        k=1;
                            fclose(pFile);
                            return 0;
                        }
                        else
                        {
                            i++;

                        }
                    }
                    if(k==0)
                    {
                    printf("No such book\n");
                    goto inquiry_state;
                    }
                }
              case 'A':
                {
                    i=0;
                    printf("Enter the author");
                    fflush(stdin);
                    fgets(search_author,60,stdin);
                    while(!feof(pFile))
                    {
                        fseek(pFile,(i*sizeof(BOOK))+60,SEEK_SET);
                        fread(&author,sizeof(BOOK),1,pFile);
                        if(strcmp(search_author,author)==0)
                        {
                        fseek(pFile,i*sizeof(BOOK),SEEK_SET);
                        fread(&title,sizeof(BOOK),1,pFile);
                        printf("Title: %s\n",title);
                        fseek(pFile,(i*sizeof(BOOK))+60,SEEK_SET);
                        fread(&search_title,sizeof(BOOK),1,pFile);
                        printf("Author: %s\n",search_author);
                        fseek(pFile,(i*sizeof(BOOK))+160,SEEK_SET);
                        fread(&book_price,sizeof(BOOK),1,pFile);
                        printf("Price: %.2f\n",book_price);
                        k=1;
                            fclose(pFile);
                            return 0;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    if(k==0)
                    {
                    printf("No such book\n");
                    goto inquiry_state;
                    }
                }
              }
    fclose(pFile);
    return 0;
}
