//
//  SplashScreen.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-05.
//

import SwiftUI

struct SplashScreen: View {
    @State private var isActiv = false
    @State private var size = 0.8
    @State private var opacity = 0.5
    
    var body: some View {
        VStack{
            VStack{
                Image(systemName: "hare.fill")
                    .font(.system(size: 80))
                    .foregroundColor(.red)
                Text("Rustic Rewards")
                    .font(Font.custom("Baskerville-Bold", size: 26))
                    .foregroundColor(.black.opacity(0.80))
            }
            .scaleEffect(size)
            .opacity(opacity)
        }
    }
}

struct SplashScreen_Previews: PreviewProvider {
    static var previews: some View {
        SplashScreen()
    }
}
