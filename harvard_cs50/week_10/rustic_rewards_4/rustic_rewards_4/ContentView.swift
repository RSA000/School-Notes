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
    @State private var userIsLoggedIn = false
    
    
    var body: some View {
        if userIsLoggedIn{
            // If user is logged in, go to ListView
            MainMenview()
        } else{
            content
        }

    }
    
    // Login and signup screen
    var content: some View{
        ZStack {
            // Background color
            Color.black.opacity(0.75)
            
            // Two rectangles
            RoundedRectangle(cornerRadius: 30, style: .continuous) .foregroundStyle(.linearGradient(colors: [.red, .gray], startPoint: .topLeading, endPoint: .bottomTrailing ))
                .opacity(0.9)
                .frame(width: 1000, height: 400)
                .rotationEffect(.degrees(155))
                .aspectRatio(contentMode: .fit)
            
            RoundedRectangle(cornerRadius: 30, style: .continuous) .foregroundStyle(.linearGradient(colors: [.red, .gray], startPoint: .topLeading, endPoint: .bottomTrailing ))
                .opacity(0.9)
                .frame(width:1000, height: 400)
                .rotationEffect(.degrees(300))
                .aspectRatio(contentMode: .fit)
            
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
                    .frame(width:350, height:1)
                    .foregroundColor(.white)
                
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
                    .frame(width:350, height:1)
                    .foregroundColor(.white)
                
                // Sign up button
                Button{
                    //Sign up
                    register()
                } label: {
                    Text("Sign Up")
                        .bold()
                        .frame(width: 200, height: 40)
                        .foregroundColor(.white)
                        .background{
                            RoundedRectangle(cornerRadius: 20, style: .continuous)
                                .fill(.linearGradient(colors: [.black], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.30)
                        }
                    
                }.offset(y:70)
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
                    
                }.offset(y: 70)
                
            }
            .frame(width: 350)
        }
        .ignoresSafeArea()
    }
    
    
    // Check if login is valid
    func login(){
        Auth.auth().signIn(withEmail: email, password: password){result, error in if error != nil{
            print(error!.localizedDescription)
            return
            }
            USER_ID = email.lowercased()
            userIsLoggedIn.toggle()
        }
    }
    
    
    // Check if register is valid
    func register(){
        Auth.auth().createUser(withEmail: email, password: password){result, error in
            if error != nil {
                print(error!.localizedDescription)
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
