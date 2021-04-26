import 'package:exersize2/HomePage.dart';
import 'package:exersize2/Models/ClassModel.dart';
import 'package:exersize2/Models/Model.dart';
import 'package:exersize2/pages/LoginProfile.dart';
import 'package:flutter/material.dart';
import 'package:hive_flutter/hive_flutter.dart';
import 'package:hive/hive.dart';

void main() async{
  await Hive.initFlutter();
  Hive.registerAdapter(UserAdapter());
  Hive.registerAdapter(ProductAdapter());
  await Hive.openBox<User>('Login');
  await Hive.openBox<Product>('Product');
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Shop',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      initialRoute:Hive.box<User>("Login").isEmpty? '/login':'/',
      routes: {
        '/':(context)=>HomePage(),
        "/login":(context)=>LoginProfile(status: true,)
      },
    );
  }
}

