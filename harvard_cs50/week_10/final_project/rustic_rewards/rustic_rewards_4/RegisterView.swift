//
//  RegisterView.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-13.
//

import SwiftUI
import Firebase


struct RegisterView: View {
    
    @State private var email = ""
    @State private var password = ""
    @State private var password_confirm = ""
    @State private var registerConfirmed = false
    @State private var text = ""
    
    
    // If account creation works, return to login
    var body: some View {
        if registerConfirmed{
            // If user is logged in, go to ListView
            ContentView()
            // Removing back button from ContentView
                .navigationBarHidden(true)
                .navigationBarTitle(Text("Home"))
                .edgesIgnoringSafeArea([.top, .bottom])
        } else{
            content
        }
    }
    
    // Login and signup screen
    var content: some View{
        ZStack {
            // Background color
            Color.black.opacity(0.75)
            
            // Two Circles
            Circle()
                .foregroundColor(.white)
                .opacity(0.95)
                .frame(width: 575)
                .padding(.horizontal)
            
            Circle()
                .foregroundColor(.red)
                .opacity(0.90)
                .frame(width: 1000)
                .ignoresSafeArea()
                .padding(.horizontal)
            
            // Background for email and password fields
            RoundedRectangle(cornerRadius: 30, style: .continuous)
                .foregroundColor(.gray)
                .frame(width: 375, height: 225)
                .opacity(0.20)
                .offset(y: 40)
            
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
                
                // Dividing rectangle
                Rectangle()
                    .frame(width:350, height:2)
                    .foregroundColor(.white)
                    .padding(.bottom, 20)
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
                
                //Password Confirmation TextField
                SecureField("Password", text: $password_confirm)
                    .foregroundColor(.white)
                    .textFieldStyle(.plain)
                    .placeholder(when: password.isEmpty){
                        Text("Confirm Password")
                            .foregroundColor(.white)
                            .bold()
                    }
                
                Rectangle()
                    .frame(width:350, height:2)
                    .foregroundColor(.white)
                    .padding(.top, -10)

                Text(text)
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
                
            }
            .frame(width: 350)
        }
        .ignoresSafeArea()
    }
    
    
    // Check if register is valid
    func register(){
        // Check if passwords match 
        if password == password_confirm{
            Auth.auth().createUser(withEmail: email, password: password){result, error in
                if error != nil {
                    print(error!.localizedDescription)
                    return
                }
                
                let db = Firestore.firestore()
                let ref = db.collection("users").document()
                
                
                ref.setData(["email": email.lowercased()])
                { err in
                    if let err = err {
                        print("Error writing document: \(err)")
                    } else {
                        print("Document successfully written!")
                    }

                }
                
                USER_ID = email.lowercased()
                registerConfirmed.toggle()
            }
        }
        else{
            self.text = "Passwords do not match"
        }
    }
}


struct RegisterView_Previews: PreviewProvider {
    static var previews: some View {
        RegisterView()
    }
}

