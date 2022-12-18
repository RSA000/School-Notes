//
//  ContentView.swift
//  rustic_admin
//
//  Created by Richard Andison on 2022-12-05.
//

import SwiftUI
import Firebase

// Admin email
var CUSTOMER_ID = ""

struct ContentView: View {

    @State private var email = ""
    @State private var password = ""
    @State private var userIsLoggedIn = false
    @State var loginError = ""
    
    
    var body: some View {
        if userIsLoggedIn{
            // If user is logged in, go to ListView
            pizzaView()
                .environmentObject(DataManager())
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
                Text("Admin")
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
                Text(loginError)
                    .bold()
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
                    
                }.offset(y: 70)
                
                
                
            }
            .frame(width: 350)
        }
        .ignoresSafeArea()
    }
    
    
    // Check if login is valid
    func login(){
        // Checking if exists in auth
        Auth.auth().signIn(withEmail: email, password: password){result, error in if error != nil{
            print(error!.localizedDescription)
            loginError = "Invalid Login"
            return
            }
            
            // Checking if employee email
            var result_count = 0
            let db = Firestore.firestore()
            let ref = db.collection("employees").whereField("email", isEqualTo: email.lowercased())
            
            // Finding documents that match email and counting results
            // Anything over 0 indicates that the person has a admin email
            ref.getDocuments{ snapshot, error in
                guard error == nil else{
                    print(error!.localizedDescription)
                    return
                }
                
                if let snapshot = snapshot{
                    for _ in snapshot.documents {
                        
                        result_count += 1
                    }
                    if result_count > 0{
                        userIsLoggedIn = true
                    }
                    else{
                        loginError = "Invalid Login Credentials"
                    }
                }
            }
            
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

