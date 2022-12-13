//
//  rustic_rewards_4App.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-01.
//

import SwiftUI
import Firebase
@main
struct rustic_rewards_4App: App {
    @StateObject var dataManager = DataManager()
    
    init(){
        FirebaseApp.configure()
    }
    
    
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
