//
//  ListView.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-02.
//

import SwiftUI


struct ListView: View {
    @EnvironmentObject var dataManager: DataManager
    
    var body: some View {
        NavigationView{
            List(dataManager.pizzas){ pizza in
                Section{
                    Text("Date: " + pizza.date).padding([.top, .trailing], 20).foregroundColor(.white)
                    Text("Points Earned: " + String(pizza.points)).foregroundColor(.white)
                    Text("Points Redeemed: " + String(pizza.redeemed)).foregroundColor(.white)
                }
                .listRowBackground(Color.gray)

            }
            .background(.red.opacity(0.75))
            .scrollContentBackground(.hidden)
        }
    }
}
    struct ListView_Previews: PreviewProvider {
        static var previews: some View {
            ListView()
                .environmentObject(DataManager())
        }
    }
