# Supermarket

Product: num, type, volume, price
Bag: type, volume, maxVolume, productCount, productArr

The system automatically packs the products at checkout according to the following rules:

  1. Only one product type can be packed in one bag
  2. The volume of all products in the bag will not exceed the maximum volume
  3. Each product will enter a bag that already has products of its kind and has space, if no such bag is found it will open a new bag
