import 'package:exersize2/Models/Model.dart';
import 'package:flutter/material.dart';
import 'package:hive/hive.dart';

class SingleProduct extends StatefulWidget {
  final int id;

  SingleProduct({this.id});

  @override
  State<StatefulWidget> createState() => SingleProductState();
}

class SingleProductState extends State<SingleProduct> {
  Product product;

  @override
  void initState() {
    // TODO: implement initState
    product = Hive.box<Product>("Product").get(widget.id);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // backgroundColor: Colors.grey[200],
      body: SafeArea(
        child: new Column(
          children: [
            new Row(
              mainAxisAlignment: MainAxisAlignment.start,
              children: [
                new Container(
                    padding: EdgeInsets.fromLTRB(25, 0, 15, 0),
                    height: 500,
                    width: 100,
                    child: new Column(
                      children: [
                        new Padding(
                            padding: EdgeInsets.symmetric(vertical: 10)),
                        new IconButton(
                            icon: Icon(Icons.arrow_back),
                            onPressed: () {
                              Navigator.pop(context);
                            }),
                      ],
                    )),
                new Container(
                  height: 500,
                  width: 380,
                  decoration: BoxDecoration(
                      color: Colors.grey[200],
                      borderRadius:
                          BorderRadius.only(bottomLeft: Radius.circular(60)),
                      image: DecorationImage(
                          image:
                              NetworkImage(product.mainImageUrl, scale: 0.6))),
                ),
              ],
            ),
            new Expanded(
                child: new Padding(
              padding: EdgeInsets.all(30),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                children: [
                  new Padding(
                    padding: EdgeInsets.only(bottom: 4),
                    child: new Text(
                      product.name,
                      style:
                          TextStyle(fontWeight: FontWeight.bold, fontSize: 22),
                    ),
                  ),
                  new Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    children: [
                      new Text(
                        product.cost != null
                            ? "\$${product.cost}"
                            : "غیر قابل فروش",
                        style: TextStyle(
                            fontWeight: FontWeight.bold,
                            color: Colors.deepOrange,
                            fontSize: 18),
                      ),
                      product.count == 0
                          ? new Container()
                          : new Row(
                              children: [
                                new GestureDetector(
                                  onTap: () {
                                    setState(() {
                                      product.count--;
                                    });
                                  },
                                  child: new CircleAvatar(
                                    radius: 15,
                                    backgroundColor: Colors.grey[200],
                                    child: new Icon(
                                      Icons.remove,
                                      color: Colors.black54,
                                    ),
                                  ),
                                ),
                                new Padding(
                                  padding: EdgeInsets.symmetric(horizontal: 10),
                                  child: new Text("${product.count}"),
                                ),
                                new GestureDetector(
                                  onTap: () {
                                    setState(() {
                                      product.count++;
                                    });
                                  },
                                  child: CircleAvatar(
                                    radius: 15,
                                    backgroundColor: Colors.deepOrange,
                                    child: new Icon(
                                      Icons.add,
                                      color: Colors.white,
                                    ),
                                  ),
                                )
                              ],
                            )
                    ],
                  ),
                  new Padding(
                    padding: EdgeInsets.only(top: 10, bottom: 15),
                    child: new Text(
                      product.name,
                      style: TextStyle(height: 1.8, color: Colors.black54),
                    ),
                  ),
                  product.count == 0 && product.cost != null
                      ? new Center(
                          child: ElevatedButton(
                            onPressed: () {
                              setState(() {
                                product.count++;
                              });
                            },
                            child: new Text(
                              "Add to cart",
                              style: TextStyle(color: Colors.white),
                            ),
                            style: ButtonStyle(
                                backgroundColor: MaterialStateProperty.all(
                                    Colors.deepOrange),
                                minimumSize:
                                    MaterialStateProperty.all(Size(200, 40))),
                          ),
                        )
                      : new Container()
                ],
              ),
            ))
          ],
        ),
      ),
    );
    throw UnimplementedError();
  }
}
