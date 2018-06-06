#ifndef __SUPER__
#define __SUPER__

typedef enum { diary, meat, neutral, fruit, vegetable, nofTypes } ProductType;

#define FILE_NAME "ProdList.bin" 

#define MAX_VOLUME 50

typedef struct
{
	int		num;
	ProductType type;
	float	volume;
	float	price;
} Product;


typedef struct
{
	ProductType type;
	float	volume;
	float	maxVolume;
	int		productCount;
	Product**	prodArr;
} Bag;

void Q1_Super();

Product** createProductArrFromFile(const char* fileName, int* totalProduct);
Bag** PackToBags(Product** allProduct, int* totalBags, int* totalProduct, const int maxVolume);
void PackToSpecificBag(Bag** bag, Product* product, const int maxVolume);
void releaseAll(Bag** allBags, Product** allProduct, int totalBags);
void releaseBag(Bag* bag);

void printProduct(const Product* pProduct);
void printBag(const Bag* pBag);
void printBagArr(const Bag** pBagArr, int count);

#endif