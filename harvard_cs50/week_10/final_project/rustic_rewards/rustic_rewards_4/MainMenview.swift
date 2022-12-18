//
//  MainMenview.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-03.
//

import SwiftUI
import Firebase

// Mainmenview
struct MainMenview: View {
    
    // Main body
    var body: some View {
        // Main navigation for points/history
            NavigationView{
                
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
                        // Points view
                        NavigationLink(destination: PointsView()            .environmentObject(DataManager()))
                        {
                            Text("Points")
                                .bold()
                                .frame(width: 270, height: 75)
                                .foregroundColor(.white)
                                .background{
                                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                                        .foregroundColor(.gray)
                                }
                                .padding(25)
                                .aspectRatio(contentMode: .fit)
                        }
                        // History view
                        NavigationLink(destination: ListView()            .environmentObject(DataManager())
)
                        {
                            Text("History")
                                .bold()
                                .frame(width: 270, height: 75)
                                .foregroundColor(.white)
                                .background{
                                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                                        .foregroundColor(.gray)
                                }
                                .padding(25)
                                .aspectRatio(contentMode: .fit)
                        }
                        
                        // Options
                        NavigationLink(destination: optionsView()            .environmentObject(DataManager())
)
                        {
                            Text("Options")
                                .bold()
                                .frame(width: 270, height: 75)
                                .foregroundColor(.white)
                                .background{
                                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                                        .foregroundColor(.gray)
                                }
                                .padding(25)
                                .aspectRatio(contentMode: .fit)
                        }
                    }
                    
                    
                }
                .ignoresSafeArea()
            }
        }
    }


struct MainMenview_Previews: PreviewProvider {
    static var previews: some View {
        MainMenview()
    }
}
