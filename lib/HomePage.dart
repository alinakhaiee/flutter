import 'package:exersize2/pages/CartBuy.dart';
import 'package:exersize2/pages/LoginProfile.dart';
import 'package:exersize2/pages/Products.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class HomePage extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => HomePageState();
}

class HomePageState extends State<HomePage> with TickerProviderStateMixin {
  TabController tabController;

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    tabController = TabController(initialIndex: 1, length: 3, vsync: this);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          toolbarHeight: 80,
          automaticallyImplyLeading: false,
          bottom: new TabBar(controller: tabController, tabs: [
            Tab(
              icon: new Icon(Icons.person),
            ),
            Tab(icon: new Icon(Icons.list_alt)),
            Tab(
              icon: new Icon(Icons.shopping_bag_outlined),
            ),
          ]),
        ),
        body: new TabBarView(controller: tabController, children: [
          new LoginProfile(status: false,),
          new Products(),
          new CartBuy()

        ]));
    throw UnimplementedError();
  }
}
