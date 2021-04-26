import 'package:exersize2/Models/ClassModel.dart';
import 'package:exersize2/components/InputTextField.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:hive/hive.dart';

class LoginProfile extends StatefulWidget {
  bool status;

  LoginProfile({@required this.status});

  @override
  State<StatefulWidget> createState() => LoginProfileState();
}

class LoginProfileState extends State<LoginProfile> {
  GlobalKey <FormState>_formkey;
  TextEditingController username = TextEditingController();
  TextEditingController password = TextEditingController();

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    _formkey = new GlobalKey<FormState>();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: new SingleChildScrollView(child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            new Stack(
              alignment: Alignment.bottomRight,
              children: [
                new Container(
                  height: 350,
                  width: 500,
                  decoration: BoxDecoration(
                      gradient: new LinearGradient(
                          colors: [
                            Colors.orange,
                            Colors.deepOrange
                          ],
                          end: Alignment.topCenter,
                          begin: Alignment.bottomCenter
                      ),
                      borderRadius: BorderRadius.only(
                        bottomLeft: Radius.circular(100),
                      )),
                  child: new Icon(
                    Icons.camera, color: Colors.white, size: 100,),
                ),
                new Padding(padding: EdgeInsets.only(bottom: 50, right: 30),
                  child: new Text(widget.status ? "Login" : "Change",
                    style: TextStyle(color: Colors.white,
                        fontWeight: FontWeight.bold,
                        fontSize: 22),),)
              ],
            ),
            new Padding(
              padding: EdgeInsets.symmetric(horizontal: 40),
              child: Container(
                  child: new Form(
                    key: _formkey,

                    child: new Column(
                      children: [
                        new InputTextField(
                            icon: Icons.email,
                            hint: "Email",
                            vlidator: (value) {
                              if(value.length>=4){return null;}
                              return "Invalid email";
                            },
                            controller:username
                        ),
                        new InputTextField(
                            icon: Icons.vpn_key,
                            hint: "Password",
                            vlidator: (value) {
                              if (value.length>=4){
                                return null;
                              }
                              return "Invalid password";
                            },
                            controller:password
                        ),
                      ],
                    ),
                  )),
            ),
            new Padding(
              padding: EdgeInsets.symmetric(horizontal: 40, vertical: 50),
              child: GestureDetector(
                onTap: () {
                  if (_formkey.currentState.validate()) {
                    handlerSave();
                  }
                },

                child: new Container(
                    height: 60,
                    width: 500,
                    decoration: BoxDecoration(
                        borderRadius: BorderRadius.circular(30),
                        gradient: new LinearGradient(
                            colors: [
                              Colors.orange,
                              Colors.deepOrange
                            ]
                        ),
                        boxShadow: [
                          BoxShadow(
                            color: Colors.grey.withOpacity(0.1),
                            spreadRadius: 1,
                            blurRadius: 2,
                            offset: Offset(0, 3), // changes position of shadow
                          ),
                        ]),
                    child: new Center(child: new Text(
                      widget.status ? "Login" : "Save", style: TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 22,
                        color: Colors.white),),)

                ),
              ),)
          ],
        )),);
    throw UnimplementedError();
  }

  handlerSave(){
   User user=new User(name: username.text,password: password.text);
   print(user);
   widget.status?Hive.box<User>('Login').add(user):Hive.box<User>("Login").put(0,user);
   Navigator.pushNamed(context,"/");
  }
}
