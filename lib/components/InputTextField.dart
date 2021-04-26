import 'package:flutter/material.dart';
import 'package:flutter/services.dart';


class InputTextField extends StatelessWidget{
  String hint;
  IconData icon;
  var vlidator;
  TextEditingController controller ;
  InputTextField({this.icon,this.hint,this.vlidator,this.controller});

  @override
  Widget build(BuildContext context) {
    return new Container(
      padding: EdgeInsets.symmetric(vertical: 8,horizontal:20),
      margin: EdgeInsets.symmetric(vertical: 20),
      height: 60,
      decoration: BoxDecoration(
          borderRadius: BorderRadius.circular(30),
          color: Colors.white,
          boxShadow: [
            BoxShadow(
              color: Colors.grey.withOpacity(0.1),
              spreadRadius: 1,
              blurRadius: 2,
              offset: Offset(0, 3), // changes position of shadow
            ),
          ]),
      child: new TextFormField(
        inputFormatters: [
          FilteringTextInputFormatter.allow(
            RegExp('[a-zA-Z0-9]')
          )
        ],
        validator:vlidator,
        controller: controller,
        decoration: InputDecoration(
          border: InputBorder.none,
          icon: Icon(icon),
          hintText: hint,
          // hintStyle: TextStyle(color: Colors.white54),
          contentPadding: EdgeInsets.fromLTRB(5, 5, 10, 5),
        ),
      ),
    );
    throw UnimplementedError();
  }

}