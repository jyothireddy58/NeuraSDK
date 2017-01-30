//
//  ViewController.swift
//  NeuraSDKApp
//
//  Created by jyothireddy on 29/01/17.
//  Copyright © 2017 JyothiReddy. All rights reserved.
//

import UIKit
import NeuraSDK

class ViewController: UIViewController
{
     var loginBtn = UIButton(type:.custom)

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        let xpos = (view.frame.size.width - 120)/2
        let ypos = (view.frame.size.height - 30)/2
        let width = CGFloat(120)
        let heigt = CGFloat(30)
        
        loginBtn =  UIButton(frame:CGRect(x:xpos,y:ypos,width:width,height:heigt))
        loginBtn.backgroundColor = UIColor.blue
        loginBtn.setTitle("Login to Neura", for: .normal)
        loginBtn.setTitleColor(UIColor.white, for: .normal)
        loginBtn.titleLabel?.font = UIFont.systemFont(ofSize: 14)
        self.view.addSubview(loginBtn)
        loginBtn.addTarget(self, action: #selector(ViewController.loginBtnclicked), for: .touchUpInside)
        self.view.addSubview(loginBtn)

        
    }
    func loginBtnclicked()
    {
        print("login button clicked")
        let permissions: Array = ["userLeftWork", "userLeftHome"]
        
        NeuraSDK.sharedInstance().authenticate(withPermissions: permissions as [String], userInfo: nil, on: self, withHandler: { (token, error) in
            if (token != nil && error == nil) {
                //Handle post-login actions
                print("you have sucessfully logged into Neura SDK")
                
            } else {
                //Handle error
                print( "error occuring")
            }
        })
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

