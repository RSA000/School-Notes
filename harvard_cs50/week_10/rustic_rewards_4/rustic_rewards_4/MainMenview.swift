//
//  MainMenview.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-03.
//

import SwiftUI

struct MainMenview: View {
    var body: some View {
            NavigationView{
                ZStack{
                    Color.red.opacity(0.75)
                    VStack{
                        NavigationLink(destination: PointsView()            .environmentObject(DataManager())
)
                        {
                            Text("Points")
                                .bold()
                                .frame(width: 300, height: 100)
                                .foregroundColor(.white)
                                .background{
                                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                                        .fill(.linearGradient(colors: [.gray], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.80)
                                }
                                .padding(50)
                                .aspectRatio(contentMode: .fit)
                        }
                        NavigationLink(destination: RedeemView()            .environmentObject(DataManager())
)
                        {
                            Text("Redeem")
                                .bold()
                                .frame(width: 300, height: 100)
                                .foregroundColor(.white)
                                .background{
                                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                                        .fill(.linearGradient(colors: [.gray], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.80)
                                }
                                .padding(50)
                                .aspectRatio(contentMode: .fit)
                        }
                        NavigationLink(destination: ListView()        .environmentObject(DataManager()))
                        {
                            Text("History")
                                .bold()
                                .frame(width: 300, height: 100)
                                .foregroundColor(.white)
                                .background{
                                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                                        .fill(.linearGradient(colors: [.gray], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.80)
                                }
                                .padding(50)
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
