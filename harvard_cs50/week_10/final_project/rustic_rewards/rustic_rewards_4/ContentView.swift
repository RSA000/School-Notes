//
//  ContentView.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-01.
//

import SwiftUI
import Firebase

var USER_ID = ""

struct ContentView: View {
    
    
    @State private var email = ""
    @State private var password = ""
    @State private var loginFailed = ""
    @State private var userIsLoggedIn = false
    @State private var registerPushed = false
    
   
    
    var body: some View {
        
        if userIsLoggedIn{
            // If user is logged in, go to ListView
            MainMenview()
        }
        else if registerPushed{
            // If user presses sign up
            RegisterView()
        }
        else{
            content
        }

    }
    
    // Login and signup screen
    var content: some View{
        
        NavigationView{
            ZStack {
                // Background color
                Color.black.opacity(0.75)
                
                
                // Two Circles
                Circle()
                    .foregroundColor(.white)
                    .opacity(0.95)
                    .frame(width: 575)
                    .ignoresSafeArea()
                    .aspectRatio(contentMode: .fit)
                
                Circle()
                    .foregroundColor(.red)
                    .opacity(0.90)
                    .frame(width: 1000)
                    .ignoresSafeArea()
                    .aspectRatio(contentMode: .fit)
                
                RoundedRectangle(cornerRadius: 30, style: .continuous)
                    .foregroundColor(.gray)
                    .frame(width: 375, height: 200)
                    .opacity(0.20)
                    .offset(y: 20)
                
              
                
                //Title
                VStack(spacing: 20){
                    Text("Rustic")
                        .foregroundColor(.white)
                        .font(.system(size: 45).bold())
                        .offset(x: -40, y:0)
                        .aspectRatio(contentMode: .fit)
                    Text("Rewards")
                        .foregroundColor(.white)
                        .font(.system(size: 45).bold())
                        .offset(x: 50, y: -20)
                        .aspectRatio(contentMode: .fit)
                    
                    
                    
                    // Email TextField
                    TextField("Email", text: $email)
                        .foregroundColor(.white)
                        .textFieldStyle(.plain)
                        .placeholder(when: email.isEmpty){
                            Text("Email")
                                .foregroundColor(.white)
                                .bold()
                        }
                    Rectangle()
                        .frame(width:350, height:2)
                        .foregroundColor(.white)
                        .padding(.top, -10)
                    
                    //Password TextField
                    SecureField("Password", text: $password)
                        .foregroundColor(.white)
                        .textFieldStyle(.plain)
                        .placeholder(when: password.isEmpty){
                            Text("Password")
                                .foregroundColor(.white)
                                .bold()
                        }
                    
                    Rectangle()
                        .frame(width:350, height:2)
                        .foregroundColor(.white)
                        .padding(.top, -10)
                    
                    // error message if login doesn't work
                    Text(loginFailed)
                        .foregroundColor(.white)
                    
                    
                    // Login Button
                    Button{
                        //Login
                        login()
                    } label: {
                        Text("Login")
                            .bold()
                            .frame(width: 200, height: 40)
                            .foregroundColor(.white)
                            .background{
                                RoundedRectangle(cornerRadius: 20, style: .continuous)
                                    .fill(.linearGradient(colors: [.black], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.30)
                            }
                    }.offset(y: 80)
                    
                    
                    
                    // Sign up button
                    NavigationLink(destination: RegisterView())
                    {
                        Text("Sign Up")
                            .bold()
                            .frame(width: 200, height: 40)
                            .foregroundColor(.white)
                            .background{
                                RoundedRectangle(cornerRadius: 20, style: .continuous)
                                    .fill(.linearGradient(colors: [.black], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.30)
                            }
                    }
                    .offset(y:75)
                }
                .frame(width: 350)
            }
            .ignoresSafeArea()
        }
    }
    
    
    // Check if login is valid
    func login(){
        Auth.auth().signIn(withEmail: email, password: password){result, error in if error != nil{
            print(error!.localizedDescription)
            loginFailed = "Invalid Username or Password"
            return
            }
            USER_ID = email.lowercased()
            userIsLoggedIn.toggle()
        }
    }
}


struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}


extension View {
    func placeholder<Content: View>(
        when shouldShow: Bool,
        alignment: Alignment = .leading,
        @ViewBuilder placeholder: () -> Content) -> some View {

        ZStack(alignment: alignment) {
            placeholder().opacity(shouldShow ? 1 : 0)
            self
        }
    }
}


