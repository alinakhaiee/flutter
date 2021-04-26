import 'package:exersize2/Models/ClassModel.dart';
import 'package:exersize2/Models/Model.dart';
import 'package:exersize2/pages/SingleProduct.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:hive/hive.dart';

class Products extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => ProductState();
}

class ProductState extends State<Products> {
  List<Product> items;
  List<Product> searchResult;

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    items = [];
    searchResult = [];
  }

  @override
  Widget build(BuildContext context) {
    items = searchResult.isNotEmpty
        ? searchResult
        : Hive.box<Product>("Product").length != 0
            ? Hive.box<Product>("Product").values.toList()
            : data;
    return new Column(
      children: [
        new Container(
          margin: EdgeInsets.symmetric(vertical: 10),
          width: 500,
          height: 200,
          decoration: BoxDecoration(
              gradient: new LinearGradient(
                colors: [
                  Colors.blueAccent[400],
                  Colors.lightBlueAccent[100],
                ],
              ),
              borderRadius: BorderRadius.circular(40)),
          child: new Padding(
            padding: EdgeInsets.only(left: 25, top: 60),
            child: Column(
              // mainAxisAlignment: MainAxisAlignment.spaceAround,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                new Text(
                  Hive.box<User>('Login').getAt(0).name,
                  style: TextStyle(
                      fontWeight: FontWeight.bold,
                      color: Colors.white,
                      fontSize: 18),
                ),
                new Container(
                  margin: EdgeInsets.symmetric(vertical: 35),
                  padding: EdgeInsets.symmetric(horizontal: 15),
                  width: 300,
                  height: 40,
                  decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(40),
                      color: Colors.white.withOpacity(0.2)),
                  child: new Row(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: [
                      new GestureDetector(
                        onTap: () {},
                        child: new Icon(
                          Icons.search,
                          color: Colors.white70,
                        ),
                      ),
                      new Expanded(
                          child: new TextField(
                        onChanged: (value) => handlerFind(value),
                        decoration: InputDecoration(
                            border: InputBorder.none,
                            hintText: "Find your ..... ",
                            hintStyle: TextStyle(color: Colors.white70),
                            contentPadding:
                                EdgeInsets.only(left: 10, bottom: 5)),
                      ))
                    ],
                  ),
                )
              ],
            ),
          ),
        ),
        new Expanded(
          child: new ListView.builder(
              padding: EdgeInsets.symmetric(horizontal: 20, vertical: 25),
              itemCount: items.length,
              itemBuilder: (context, index) {
                return new GestureDetector(
                  onTap: () {
                    Hive.box<Product>("Product")
                        .put(items[index].productId, items[index]);
                    Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) =>
                                SingleProduct(id: items[index].productId)));
                  },
                  child: new Container(
                    margin: EdgeInsets.only(bottom: 30),
                    padding: EdgeInsets.symmetric(horizontal: 15, vertical: 15),
                    height: 130,
                    decoration: BoxDecoration(
                        borderRadius: BorderRadius.circular(10),
                        color: Colors.white,
                        boxShadow: [
                          BoxShadow(
                            color: Colors.grey.withOpacity(0.3),
                            spreadRadius: 2,
                            blurRadius: 2,
                            offset: Offset(1, 3), // changes position of shadow
                          ),
                        ]),
                    child: new Row(
                      mainAxisAlignment: MainAxisAlignment.start,
                      children: [
                        new SizedBox(
                          height: 110,
                          width: 100,
                          child: new Image(
                            image: NetworkImage(items[index].mainImageUrl),
                            fit: BoxFit.cover,
                          ),
                        ),
                        new Expanded(
                            child: new Padding(
                          padding: EdgeInsets.only(left: 40, right: 10),
                          child: Column(
                            crossAxisAlignment: CrossAxisAlignment.start,
                            mainAxisAlignment: MainAxisAlignment.spaceAround,
                            children: [
                              new Text(
                                items[index].name,
                                maxLines: 1,
                                style: TextStyle(
                                  fontWeight: FontWeight.bold,
                                  fontSize: 18,
                                ),
                              ),
                              new Row(
                                mainAxisAlignment:
                                    MainAxisAlignment.spaceBetween,
                                children: [
                                  new Column(
                                    crossAxisAlignment:
                                        CrossAxisAlignment.start,
                                    children: [
                                      new Text(
                                        items[index].cost != 0 &&
                                                items[index].cost != null
                                            ? "Price:\$${items[index].cost}"
                                            : "",
                                        style: TextStyle(
                                            fontWeight: FontWeight.bold,
                                            color: Colors.black54,
                                            fontSize: 16),
                                      ),
                                      new Text(
                                          items[index].offPercent != 0 &&
                                                  items[index].offPercent !=
                                                      null
                                              ? "OffPercent:%${items[index].offPercent}"
                                              : "",
                                          style: TextStyle(
                                              fontWeight: FontWeight.bold,
                                              color: Colors.black54,
                                              fontSize: 16)),
                                      new Text(
                                          items[index].offPercent != 0 &&
                                                  items[index].offPercent !=
                                                      null
                                              ? "FinalPrice:${handlerPrice(index)}"
                                              : "",
                                          style: TextStyle(
                                              fontWeight: FontWeight.bold,
                                              color: Colors.black54,
                                              fontSize: 16))
                                    ],
                                  ),
                                  items[index].count != 0
                                      ? new Row(
                                          children: [
                                            Icon(Icons.shopping_basket),
                                            new Padding(padding: EdgeInsets.symmetric(horizontal: 5)),
                                            new Text("${items[index].count}")
                                          ],
                                        )
                                      : new Container()
                                ],
                              )
                            ],
                          ),
                        )),
                        Hive.box<Product>("Product").isEmpty
                            ? new Container()
                            : new GestureDetector(
                                onTap: () {
                                  print("del");
                                  Hive.box<Product>("Product")
                                      .delete(items[index].productId);
                                  setState(() {});
                                },
                                child: CircleAvatar(
                                  backgroundColor: Colors.grey,
                                  child: new Icon(
                                    Icons.delete_forever,
                                    color: Colors.white,
                                  ),
                                ),
                              )
                      ],
                    ),
                  ),
                );
              }),
        ),
      ],
    );

    throw UnimplementedError();
  }

  handlerFind(String value) {
    List<Product> find = [];
    if (value.trim().isNotEmpty) {
      items.forEach((element) {
        if (element.name.contains(value)) {
          find.add(element);
        }
      });
    }
    // }).toList();
    print(find);

    setState(() {
      searchResult = find;
    });
  }
  double handlerPrice(int index){
   return (items[index].cost - (items[index].cost * items[index].offPercent) / 100);
   
  }
}
