#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "QSuper.h"

const char TypeStr[nofTypes][15] = { "diary", "meat", "neutral", "fruit", "vegetable" };

void Q1_Super()
{
	int totalProduct;
	int totalBags;
	Product** allProduct = NULL;
	Bag** allBags = NULL;
	
	allProduct = createProductArrFromFile(FILE_NAME, &totalProduct);
	allBags = PackToBags(allProduct, &totalBags, &totalProduct, MAX_VOLUME);
	printBagArr(allBags, totalBags);
	releaseAll(allBags, allProduct, totalBags);
}

Product** createProductArrFromFile(const char* fileName, int* totalProduct)
{
	int i;
	Product** allProduct;
	FILE* f = fopen(fileName, "rb");
	if (!f)
		return NULL;
	fread(totalProduct, sizeof(int), 1, f);
	allProduct = (Product**)malloc(*totalProduct*sizeof(Product*));
	for (i = 0; i < *totalProduct; i++)
	{
		allProduct[i] = (Product*)malloc(sizeof(Product));
		fread(allProduct[i], sizeof(Product), 1, f);;
	}
	fclose(f);
	return allProduct;
}

Bag** PackToBags(Product** allProduct, int* totalBags, int* totalProduct, const int maxVolume)
{
	int packed = 0;
	int i, j;
	Bag** allBags = (Bag**)malloc(sizeof(Bag*));
	*totalBags = 0;
	for (i = 0; i < *totalProduct; i++)
	{
		for (j = 0; j < *totalBags; j++)
		{
			if (allProduct[i]->type == allBags[j]->type && (allBags[j]->volume+allProduct[i]->volume) <= allBags[j]->maxVolume)
			{
				PackToSpecificBag(&allBags[j], allProduct[i], maxVolume);
				packed = 1;
			}
		}
		if (!packed)
		{
			(*totalBags)++;
			allBags = (Bag**)realloc(allBags, *totalBags*sizeof(Bag));
			allBags[j] = NULL;
			PackToSpecificBag(&allBags[j], allProduct[i], maxVolume);
		}
		packed = 0;
	}
	return allBags;
}

void PackToSpecificBag(Bag** bag, Product* product, const int maxVolume)
{
	if (!*bag)
	{
		(*bag) = (Bag*)malloc(sizeof(Bag));
		(*bag)->prodArr = (Product**)malloc(sizeof(Product*));
		(*bag)->volume = product->volume;
		(*bag)->productCount = 1;
	}
	else
	{
		(*bag)->productCount++;
		(*bag)->prodArr = (Product**)realloc((*bag)->prodArr, (*bag)->productCount*sizeof(Product*));
		(*bag)->volume += product->volume;
	}
	(*bag)->type = product->type;
	(*bag)->maxVolume = maxVolume;
	(*bag)->prodArr[(*bag)->productCount-1] = product;
}

void releaseAll(Bag** allBags, Product** allProduct, int totalBags)
{
	int i;
	for (i = 0; i < totalBags; i++)
		releaseBag(allBags[i]);
	free(allBags);
	free(allProduct);
}

void releaseBag(Bag* bag)
{
	int i;
	for (i = 0; i < bag->productCount; i++)
		free(bag->prodArr[i]);
	free(bag->prodArr);
	free(bag);
}

void printProduct(const Product* pProduct)
{
	printf("product %d type:%s volume: %.2f price: %.2f \n", pProduct->num, TypeStr[pProduct->type],
		pProduct->volume, pProduct->price);
}

void printBag(const Bag* pBag)
{
	int i;
	printf("Beg Type %s\t", TypeStr[pBag->type]);
	printf("volume %.2f out of %.2f\n", pBag->volume, pBag->maxVolume);
	printf("There are %d products in the beg\n", pBag->productCount);
	for (i = 0; i < pBag->productCount; i++)
		printProduct(pBag->prodArr[i]);
}

void printBagArr(const Bag** pBagArr, int count)
{
	int i;
	printf("There are %d begs in the super\n", count);
	for (i = 0; i < count; i++)
		printBag(pBagArr[i]);
}


