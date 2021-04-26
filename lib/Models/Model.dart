import 'package:flutter/material.dart';
import 'package:hive/hive.dart';

part 'Model.g.dart';

@HiveType(typeId: 2)
class Product {
  @HiveField(0)
  int productId;
  @HiveField(1)
  String name;
  @HiveField(2)
  String mainImageUrl;
  @HiveField(3)
  int cost;
  @HiveField(4)
  int offPercent;
  @HiveField(5)
  int count;

  Product(
      {this.name,
      this.cost,
      this.mainImageUrl,
      this.offPercent,
      this.productId,
      this.count});
}

List<Product> data = [
  new Product(
      productId: 4839,
      name: "پودر خامه كيك و شيريني با طعم وانيل فلورا - 200 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: 411,
      offPercent: 15,
      count: 0),
  new Product(
      productId: 4838,
      name: "پودر كيك رد ولوت رشد مقدار 600 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: null,
      offPercent: null,
      count: 0),
  new Product(
      productId: 4837,
      name: "پودر كيك وانيلي رشد - 500 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: 12800,
      offPercent: 10,
      count: 0),
  new Product(
      productId: 4836,
      name: "ارد نشاسته تردك - 200 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: 25000,
      offPercent: 10,
      count: 0),
  new Product(
      productId: 4835,
      name: "ارد ذرت ارينا - 200 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: null,
      offPercent: null,
      count: 0),
  new Product(
      productId: 3693,
      name: "كنسرو مرغ شيلانه - 150 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: 13750,
      offPercent: 40,
      count: 0),
  new Product(
      productId: 3692,
      name: "كنسرو مرغ در روغن شيلتون وزن 180 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: 15000,
      offPercent: 0,
      count: 0),
  new Product(
      productId: 3691,
      name: "كنسرو مرغ چينود وزن 150 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: 15800,
      offPercent: 0,
      count: 0),
  new Product(
      productId: 3690,
      name: "كنسرو مرغ سالي - 150 گرم",
      mainImageUrl:
          "https://www.fakherleather.com/wp-content/uploads/2019/11/women-collection-2020-fakherleather.jpg",
      cost: 14000,
      offPercent: 0,
      count: 0)
];
