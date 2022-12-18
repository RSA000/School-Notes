//
//  optionsView.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-17.
//

import SwiftUI
import Firebase


struct optionsView: View {
    
    @State private var logout = false
    
    var body: some View {
        if logout == true{
            ContentView()
                .navigationBarBackButtonHidden(true)
        }
        else{
            content
        }
    }

    var content: some View{
            
            ZStack(alignment: .center){
                Color.black.opacity(0.75)
                
                Circle()
                    .foregroundColor(.white)
                    .opacity(0.95)
                    .frame(width: 575)
                
                Circle()
                    .foregroundColor(.red)
                    .opacity(0.90)
                    .frame(width: 1000)
                    .ignoresSafeArea()
                VStack{
                    
                    // Change Password
                    NavigationLink(destination: changePasswordView()            .environmentObject(DataManager())
                    )
                    {
                        Text("Change Password")
                            .bold()
                            .frame(width: 200, height: 40)
                            .foregroundColor(.white)
                            .background{
                                RoundedRectangle(cornerRadius: 20, style: .continuous)
                                    .foregroundColor(.gray)
                            }
                            .padding(25)
                            .aspectRatio(contentMode: .fit)
                    }
                }
                
                Button{
                    // Logout
                    USER_ID = ""
                    logout = true
                    
                } label: {
                    Text("Logout")
                        .bold()
                        .frame(width: 200, height: 40)
                        .foregroundColor(.white)
                        .background{
                            RoundedRectangle(cornerRadius: 20, style: .continuous)
                                .foregroundColor(.gray)
                        }
                }.offset(y: 80)
                
                
            }
            .ignoresSafeArea()
        }
    }

struct optionsView_Previews: PreviewProvider {
    static var previews: some View {
        optionsView()
    }
}
