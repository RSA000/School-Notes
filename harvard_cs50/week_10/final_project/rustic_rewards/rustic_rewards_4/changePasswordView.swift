//
//  changePasswordView.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-17.
//

import SwiftUI
import Firebase
import FirebaseAuth

struct changePasswordView: View {
    
    @State private var password = ""
    @State private var password_confirm = ""
    @State private var changePasswordConfirmed = false
    @State private var text = ""
    
    
    // If account creation works, return to login
    var body: some View {
        if changePasswordConfirmed{
            // If user is logged in, go to ListView
            ContentView()
                .navigationBarBackButtonHidden(true)
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
                .frame(width: 375, height: 150)
                .opacity(0.20)
                .offset(y: -10)
            
            //Title
            VStack(spacing: 20){
                Text("Change Password")
                    .foregroundColor(.white)
                    .font(.system(size: 30).bold())
                    .offset(x: -40, y:0)
                    .aspectRatio(contentMode: .fit)
                
                
                
                //Password TextField
                SecureField("Password", text: $password)
                    .foregroundColor(.white)
                    .textFieldStyle(.plain)
                    .placeholder(when: password.isEmpty){
                        Text("New Password")
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
                
                // Change password
                Button{
                    //change password
                    changePassword()
                } label: {
                    Text("Change password")
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
    
    
    // Change Password
    func changePassword(){
        if password == password_confirm{
            let user = Auth.auth().currentUser;
            let newPassword = password

            user?.updatePassword(to: password)
            changePasswordConfirmed = true
            

        }
    }
}


struct changePasswordView_Previews: PreviewProvider {
    static var previews: some View {
        changePasswordView()
    }
}
